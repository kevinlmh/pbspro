add_custom_command(OUTPUT job_attr_def.c
	COMMAND ${Python3_EXECUTABLE}
		${CMAKE_SOURCE_DIR}/buildutils/attr_parser.py
		-m ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_job_attr_def.xml
		-s ${CMAKE_CURRENT_BINARY_DIR}/job_attr_def.c
	MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_job_attr_def.xml
)
add_custom_command(OUTPUT resc_def_all.c
	COMMAND ${Python3_EXECUTABLE}
		${CMAKE_SOURCE_DIR}/buildutils/attr_parser.py
		-m ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_resc_def_all.xml
		-s ${CMAKE_CURRENT_BINARY_DIR}/resc_def_all.c
	MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_resc_def_all.xml
)
add_executable(pbs_mom
	job_attr_def.c
	resc_def_all.c
	${CMAKE_SOURCE_DIR}/src/lib/Libpython/shared_python_utils.c
	${CMAKE_SOURCE_DIR}/src/server/mom_info.c
	${CMAKE_SOURCE_DIR}/src/server/attr_recov.c
	${CMAKE_SOURCE_DIR}/src/server/dis_read.c
	${CMAKE_SOURCE_DIR}/src/server/job_func.c
	${CMAKE_SOURCE_DIR}/src/server/process_request.c
	${CMAKE_SOURCE_DIR}/src/server/reply_send.c
	${CMAKE_SOURCE_DIR}/src/server/req_quejob.c
	${CMAKE_SOURCE_DIR}/src/server/resc_attr.c
	${CMAKE_SOURCE_DIR}/src/server/vnparse.c
	${CMAKE_SOURCE_DIR}/src/server/setup_resc.c
	${PBS_MACH}/mom_mach.c
	${PBS_MACH}/mom_mach.h
	${PBS_MACH}/mom_start.c
	${PBS_MACH}/pe_input.c
	catch_child.c
	job_recov_fs.c
	mock_run.c
	mock_run.h
	mom_comm.c
	mom_hook_func.c
	mom_inter.c
	mom_main.c
	mom_pmix.c
	mom_pmix.h
	mom_server.c
	mom_vnode.c
	mom_walltime.c
	popen.c
	prolog.c
	requests.c
	rm_dep.h
	stage_func.c
	start_exec.c
	vnode_storage.c
	renew_creds.c
	renew_creds.h
)
# add_dependencies(pbs_mom
# 	${CMAKE_BUILD_DIR}/src/lib/Libattr/job_attr_def.c
# 	${CMAKE_BUILD_DIR}/src/lib/Libattr/resc_def_all.c
# )
target_include_directories(pbs_mom
	PRIVATE
	${CMAKE_SOURCE_DIR}/src/include
	${CMAKE_BINARY_DIR}/src/include
	${HwLoc_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIRS}
	${Python3_INCLUDE_DIRS}
	${PBS_MACH}
	${CMAKE_BINARY_DIR}/src/lib/Libattr
	# @pmix_inc@
	# @KRB5_CFLAGS@
)
target_link_libraries(pbs_mom
	PRIVATE
	${CMAKE_BINARY_DIR}/src/lib/Libattr/libattr.a
	${CMAKE_BINARY_DIR}/src/lib/Libpbs/libpbs_static.a
	${CMAKE_BINARY_DIR}/src/lib/Libtpp/libtpp.a
	${CMAKE_BINARY_DIR}/src/lib/Liblog/liblog.a
	${CMAKE_BINARY_DIR}/src/lib/Libnet/libnet.a
	${CMAKE_BINARY_DIR}/src/lib/Libsec/libsec.a
	${CMAKE_BINARY_DIR}/src/lib/Libsite/libsite.a
	${CMAKE_BINARY_DIR}/src/lib/Libutil/libutil.a
	${HwLoc_LIBRARIES}
	${Python3_LIBRARIES}
	${ZLIB_LIBRARIES}
	OpenSSL::SSL
	OpenSSL::Crypto
	Threads::Threads
	${CMAKE_DL_LIBS} 
	# @pmix_lib@
	# @PYTHON_LDFLAGS@
	# @mom_mach_libs@
	# @KRB5_LIBS@)
)
if(${PBS_UNDOLR_ENABLED})
  target_include_directories(pbs_mom PRIVATE ${UndoLR_INCLUDE_DIR})
endif()
target_compile_definitions(pbs_mom PRIVATE PBS_MOM PYTHON HWLOC)

# if ALPS_ENABLED
# pbs_mom_CPPFLAGS += -DMOM_ALPS=1 @expat_inc@
# pbs_mom_LDADD += @expat_lib@
# pbs_mom_SOURCES += linux/alps.c
# endif

install(TARGETS pbs_mom DESTINATION ${CMAKE_INSTALL_SBINDIR})