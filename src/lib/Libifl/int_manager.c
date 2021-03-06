/*
 * Copyright (C) 1994-2020 Altair Engineering, Inc.
 * For more information, contact Altair at www.altair.com.
 *
 * This file is part of both the OpenPBS software ("OpenPBS")
 * and the PBS Professional ("PBS Pro") software.
 *
 * Open Source License Information:
 *
 * OpenPBS is free software. You can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * OpenPBS is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Commercial License Information:
 *
 * PBS Pro is commercially licensed software that shares a common core with
 * the OpenPBS software.  For a copy of the commercial license terms and
 * conditions, go to: (http://www.pbspro.com/agreement.html) or contact the
 * Altair Legal Department.
 *
 * Altair's dual-license business model allows companies, individuals, and
 * organizations to create proprietary derivative works of OpenPBS and
 * distribute them - whether embedded or bundled with other software -
 * under a commercial license agreement.
 *
 * Use of Altair's trademarks, including but not limited to "PBS™",
 * "OpenPBS®", "PBS Professional®", and "PBS Pro™" and Altair's logos is
 * subject to Altair's trademark licensing policies.
 */

/**
 * @file	int_manager.c
 *
 * @brief
 * The function that underlies most of the job manipulation
 * routines...
 */

#include <pbs_config.h>   /* the master config generated by configure */

#include <stdio.h>
#include "libpbs.h"
#include "pbs_ecl.h"
#include "cmds.h"


extern char * PBS_get_server(char *, char *, uint *);


/**
 * @brief
 *	-send manager request and read reply.
 *
 * @param[in] c - communication handle
 * @param[in] function - req type
 * @param[in] command - command
 * @param[in] objtype - object type
 * @param[in] objname - object name
 * @param[in] aoplp - attribute list
 * @param[in] extend - extend string for req
 *
 * @return	int
 * @retval	0	success
 * @retval	!0	error
 *
 */
int
PBSD_manager(int c, int function, int command, int objtype, char *objname, struct attropl *aoplp, char *extend)
{
	int i;
	struct batch_reply *reply;
	int rc = 0;
	int agg_rc = 0;
	svr_conn_t *svr_connections = get_conn_svr_instances(c);
	int num_cfg_svrs = get_num_servers();
	char server_out[MAXSERVERNAME + 1];
	char server_name[PBS_MAXSERVERNAME + 1];
	int single_itr = 0;
	char job_id_out[PBS_MAXCLTJOBID];
	uint server_port;
	int start = 0;
	int ct = 0;

	if (!svr_connections)
		return PBSE_NOSERVER;

	/* initialize the thread context data, if not initialized */
	if (pbs_client_thread_init_thread_context() != 0)
		return pbs_errno;

	/* verify the object name if creating a new one */
	if (command == MGR_CMD_CREATE)
		if (pbs_verify_object_name(objtype, objname) != 0)
			return pbs_errno;

	/* now verify the attributes, if verification is enabled */
	if (pbs_verify_attributes(random_srv_conn(svr_connections), function, objtype, command, aoplp))
		return pbs_errno;

	if ((objtype == MGR_OBJ_JOB) && (get_server(objname, job_id_out, server_out) == 0)) {
		if (PBS_get_server(server_out, server_name, &server_port)) {
			single_itr = 1;
			for (i = 0; i < num_cfg_svrs; i++) {
				if (!strcmp(server_name, pbs_conf.psi[i].name) && server_port == pbs_conf.psi[i].port) {
					start = i;
					break;
				}
			}
		}
	}

	for (i = start, ct = 0; ct < num_cfg_svrs; i = (i + 1) % num_cfg_svrs, ct++) {

		if (svr_connections[i].state != SVR_CONN_STATE_UP) {
			pbs_errno = PBSE_NOSERVER;
			agg_rc = pbs_errno;
			continue;
		}

		c = svr_connections[i].sd;

		/* lock pthread mutex here for this connection */
		/* blocking call, waits for mutex release */
		if (pbs_client_thread_lock_connection(c) != 0)
			return pbs_errno;

		/* send the manage request */
		rc = PBSD_mgr_put(c, function, command, objtype, objname, aoplp, extend, PROT_TCP, NULL);
		if (rc) {
			pbs_client_thread_unlock_connection(c);
			return rc;
		}

		/* read reply from stream into presentation element */
		reply = PBSD_rdrpy(c);
		PBSD_FreeReply(reply);

		rc = get_conn_errno(c);
		if (rc != 0)
			agg_rc = rc;

		/* unlock the thread lock and update the thread context data */
		if (pbs_client_thread_unlock_connection(c) != 0)
			return pbs_errno;

		if ((agg_rc == PBSE_NONE) && single_itr)
			break;
	}

	return (pbs_errno = agg_rc);
}
