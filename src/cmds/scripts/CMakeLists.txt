# configure_file(pbsrun.bgl.init.in pbsrun.bgl.init @ONLY)
# configure_file(pbsrun.ch_gm.init.in pbsrun.ch_gm.init @ONLY)
# configure_file(pbsrun.ch_mx.init.in pbsrun.ch_mx.init @ONLY)
# configure_file(pbsrun.gm_mpd.init.in pbsrun.gm_mpd.init @ONLY)
# configure_file(pbsrun.intelmpi.init.in pbsrun.intelmpi.init @ONLY)
# configure_file(pbsrun.mpich2.init.in pbsrun.mpich2.init @ONLY)
# configure_file(pbsrun.mvapich1.init.in pbsrun.mvapich1.init @ONLY)
# configure_file(pbsrun.mvapich2.init.in pbsrun.mvapich2.init @ONLY)
# configure_file(pbsrun.mx_mpd.init.in pbsrun.mx_mpd.init @ONLY)
configure_file(pbs_habitat.in pbs_habitat @ONLY)
configure_file(pbs_init.d.in pbs_init.d @ONLY)
configure_file(pbs_poerun.in pbs_poerun @ONLY)
configure_file(pbs_postinstall.in pbs_postinstall @ONLY)
configure_file(modulefile.in modulefile @ONLY)

install(FILES
  limits.pbs_mom.compat
  RENAME limits.pbs_mom
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/init.d
)
install(FILES
  limits.post_services.compat
  RENAME limits.post_services
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/init.d
)
install(FILES
  limits.pbs_mom.compat
  limits.post_services.compat
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/init.d
)
# install(FILES
#   ${CMAKE_CURRENT_BINARY_DIR}/pbsrun.bgl.init
#   ${CMAKE_CURRENT_BINARY_DIR}/pbsrun.ch_gm.init
#   ${CMAKE_CURRENT_BINARY_DIR}/pbsrun.ch_mx.init
#   ${CMAKE_CURRENT_BINARY_DIR}/pbsrun.gm_mpd.init
#   ${CMAKE_CURRENT_BINARY_DIR}/pbsrun.intelmpi.init
#   ${CMAKE_CURRENT_BINARY_DIR}/pbsrun.mpich2.init
#   ${CMAKE_CURRENT_BINARY_DIR}/pbsrun.mvapich1.init
#   ${CMAKE_CURRENT_BINARY_DIR}/pbsrun.mvapich2.init
#   ${CMAKE_CURRENT_BINARY_DIR}/pbsrun.mx_mpd.init
#   sgiMPI.awk
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/MPI
# )
install(FILES
  pbsrun.bgl.init.in
  pbsrun.ch_gm.init.in
  pbsrun.ch_mx.init.in
  pbsrun.gm_mpd.init.in
  pbsrun.intelmpi.init.in
  pbsrun.mpich2.init.in
  pbsrun.mvapich1.init.in
  pbsrun.mvapich2.init.in
  pbsrun.mx_mpd.init.in
  sgiMPI.awk
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/MPI
)
install(PROGRAMS
  pbs_bootcheck.py
  pbs_topologyinfo.py
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/python
)
# these two files will be copied to /etc/profile.d by postinstall script
install(PROGRAMS
  pbs.csh
  pbs.sh
  DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/profile.d # /etc/profile.d 
)
# install(FILES
#   pbs.service
#   DESTINATION @_unitdir@ DATA)
install(PROGRAMS
  ${CMAKE_CURRENT_BINARY_DIR}/pbs_habitat
  ${CMAKE_CURRENT_BINARY_DIR}/pbs_init.d
  ${CMAKE_CURRENT_BINARY_DIR}/pbs_postinstall
  pbs_preuninstall
  pbs_posttrans
  DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)
install(PROGRAMS
  pbs_topologyinfo
  printjob
  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(PROGRAMS
  pbs_dataservice
  pbs_ds_password
  pbs_server
  pbs_snapshot
  DESTINATION ${CMAKE_INSTALL_SBINDIR}
)
# will be copied to /opt/modulefiles by postinstall script
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/modulefile
  DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}
)

# dist_sysconf_DATA = \
#   modulefile 

# CLEANFILES = \
# 	pbs_init.d \
# 	limits.pbs_mom \
#   limits.post_services