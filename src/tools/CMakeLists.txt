
set(COMMON_INCLUDES
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
)
set(COMMON_LIBS
  ${CMAKE_BINARY_DIR}/src/lib/Libpbs/libpbs_static.a
  ${CMAKE_BINARY_DIR}/src/lib/Libnet/libnet.a
  ${CMAKE_BINARY_DIR}/src/lib/Libsec/libsec.a
  ${CMAKE_BINARY_DIR}/src/lib/Libutil/libutil.a
  Threads::Threads
  # ${CMAKE_DL_LIBS} 
  # nsl
)

add_executable(pbs_sleep pbs_sleep.c)
target_include_directories(pbs_sleep PRIVATE ${COMMON_INCLUDES})
# target_link_options(pbs_sleep PRIVATE -all-static) # not working

add_executable(chk_tree chk_tree.c)
target_include_directories(chk_tree PRIVATE ${COMMON_INCLUDES} ${ZLIB_INCLUDE_DIRS})
target_compile_definitions(chk_tree PRIVATE PBS_COMPRESSION_ENABLED)
target_link_libraries(chk_tree
  PRIVATE
  ${CMAKE_BINARY_DIR}/src/lib/Liblog/liblog.a
  ${COMMON_LIBS}
  ${CMAKE_BINARY_DIR}/src/lib/Libtpp/libtpp.a
  ${ZLIB_LIBRARIES}
  ${CMAKE_DL_LIBS}
)
add_executable(pbs_ds_monitor
  pbs_ds_monitor.c
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
)
target_include_directories(pbs_ds_monitor PRIVATE ${COMMON_INCLUDES})
# target_link_options(pbs_ds_monitor PRIVATE -Wl,-rpath,${CMAKE_INSTALL_LIBDIR})
target_link_libraries(pbs_ds_monitor
  ${CMAKE_BINARY_DIR}/src/lib/Libdb/pgsql/libdb.so
  ${COMMON_LIBS}
  ${PostgreSQL_LIBRARIES}
  OpenSSL::SSL
  OpenSSL::Crypto
  ${CMAKE_DL_LIBS}
)

add_executable(pbs_idled
  pbs_idled.c
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
)
target_include_directories(pbs_idled
  PRIVATE
  ${COMMON_INCLUDES}
  ${X11_INCLUDE_DIR}
)
target_link_libraries(pbs_idled
  PRIVATE
  ${COMMON_LIBS}
  ${X11_LIBRARIES}
  ${CMAKE_DL_LIBS}
)

add_executable(pbs_hostn hostn.c)
target_include_directories(pbs_hostn PRIVATE ${COMMON_INCLUDES})
target_link_libraries(pbs_hostn PRIVATE ${COMMON_LIBS})

add_executable(pbs_probe
  pbs_probe.c
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
)
target_include_directories(pbs_probe
  PRIVATE
  ${COMMON_INCLUDES}
  ${Python3_INCLUDE_DIRS}
)
target_link_libraries(pbs_probe
  PRIVATE
  ${COMMON_LIBS}
  ${Python3_LIBRARIES}
  ${CMAKE_DL_LIBS}
)

function(gen_attrdef_file name)
	add_custom_command(OUTPUT ${name}.c
		COMMAND ${Python3_EXECUTABLE}
			${CMAKE_SOURCE_DIR}/buildutils/attr_parser.py
			-m ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_${name}.xml
			-s ${CMAKE_CURRENT_BINARY_DIR}/${name}.c
		MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_${name}.xml)
endfunction()
gen_attrdef_file(job_attr_def)
gen_attrdef_file(node_attr_def)
gen_attrdef_file(queue_attr_def)
gen_attrdef_file(resc_def_all)
gen_attrdef_file(resv_attr_def)
gen_attrdef_file(sched_attr_def)
gen_attrdef_file(svr_attr_def)

add_executable(pbs_python
  job_attr_def.c
  node_attr_def.c
  queue_attr_def.c
  resc_def_all.c
  resv_attr_def.c
  svr_attr_def.c
  ${CMAKE_SOURCE_DIR}/src/server/svr_attr.c
  ${CMAKE_SOURCE_DIR}/src/server/resc_attr.c
  ${CMAKE_SOURCE_DIR}/src/server/setup_resc.c
  ${CMAKE_SOURCE_DIR}/src/server/vnparse.c
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
  pbs_python.c
)
target_include_directories(pbs_python
  PRIVATE
  ${COMMON_INCLUDES}
  ${Python3_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}/src/lib/Libattr
)
target_link_libraries(pbs_python
  PRIVATE
  ${CMAKE_BINARY_DIR}/src/lib/Libpython/libpbspython.a
	${CMAKE_BINARY_DIR}/src/lib/Liblog/liblog.a
  ${CMAKE_BINARY_DIR}/src/lib/Libattr/libattr.a
  ${CMAKE_BINARY_DIR}/src/lib/Libnet/libnet.a
  ${COMMON_LIBS}
  ${Python3_LIBRARIES}
  ${CMAKE_DL_LIBS}
)
target_compile_definitions(pbs_python PRIVATE -DPBS_PYTHON=1.1)

add_executable(pbs_tclsh pbs_tclWrap.c site_tclWrap.c pbsTclInit.c)
target_include_directories(pbs_tclsh
  PRIVATE
  ${COMMON_INCLUDES}
  ${ZLIB_INCLUDE_DIRS}
  ${TCL_INCLUDE_PATH}
)
target_link_libraries(pbs_tclsh
  PRIVATE
  ${COMMON_LIBS}
  ${CMAKE_BINARY_DIR}/src/lib/Libtpp/libtpp.a
  ${CMAKE_BINARY_DIR}/src/lib/Liblog/liblog.a
  Threads::Threads
  # socket_lib
  ${ZLIB_LIBRARIES}
  ${TCL_LIBRARY}
  ${CMAKE_DL_LIBS}
)

add_executable(pbs_upgrade_job pbs_upgrade_job.c)
target_include_directories(pbs_upgrade_job
  PRIVATE
  ${COMMON_INCLUDES}
  ${CMAKE_BINARY_DIR}/src/lib/Libattr
)
target_link_libraries(pbs_upgrade_job PRIVATE ${COMMON_LIBS})

add_executable(pbs_wish pbs_tclWrap.c site_tclWrap.c pbsTkInit.c)
target_include_directories(pbs_wish
  PRIVATE
  ${COMMON_INCLUDES}
  ${ZLIB_INCLUDE_DIRS}
  ${TCL_INCLUDE_PATH}
  ${TK_INCLUDE_PATH}
)
target_link_libraries(pbs_wish
  PRIVATE
  ${COMMON_LIBS}
  ${CMAKE_BINARY_DIR}/src/lib/Libtpp/libtpp.a
  ${CMAKE_BINARY_DIR}/src/lib/Liblog/liblog.a
  ${CMAKE_BINARY_DIR}/src/lib/Libnet/libnet.a
  Threads::Threads
  # socket_lib
  ${ZLIB_LIBRARIES}
  ${TCL_LIBRARY}
  ${TK_LIBRARY}
  ${CMAKE_DL_LIBS}
)

add_executable(printjob.bin
  printjob.c
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
)
target_include_directories(printjob.bin
  PRIVATE
  ${COMMON_INCLUDES}
  ${CMAKE_BINARY_DIR}/src/lib/Libattr)
target_link_libraries(printjob.bin
PRIVATE
${COMMON_LIBS}
${CMAKE_DL_LIBS})

add_executable(printjob_svr.bin
  printjob.c
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
)
target_include_directories(printjob_svr.bin
  PRIVATE
  ${COMMON_INCLUDES}
  ${CMAKE_SOURCE_DIR}/src/lib/Libdb/pgsql
  ${CMAKE_BINARY_DIR}/src/lib/Libattr
  ${PostgreSQL_INCLUDE_DIRS}
)
target_compile_definitions(printjob_svr.bin PRIVATE PRINTJOBSVR)
target_link_libraries(printjob_svr.bin
  PRIVATE
  ${PostgreSQL_LIBRARIES}
  ${CMAKE_BINARY_DIR}/src/lib/Libdb/pgsql/libdb.so
  ${COMMON_LIBS}
  OpenSSL::SSL
  OpenSSL::Crypto
  ${CMAKE_DL_LIBS}
)

add_executable(rstester
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
  tracejob.c
  tracejob.h
)
target_include_directories(rstester PRIVATE ${COMMON_INCLUDES})
target_link_libraries(rstester PRIVATE ${COMMON_LIBS} ${CMAKE_DL_LIBS})

add_executable(tracejob
  tracejob.c
  tracejob.h
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
)
target_include_directories(tracejob PRIVATE ${COMMON_INCLUDES})
target_link_libraries(tracejob PRIVATE ${COMMON_LIBS} ${CMAKE_DL_LIBS})

install(TARGETS
  pbs_hostn
  pbs_python
  pbs_tclsh
  pbs_wish
  printjob.bin
  printjob_svr.bin
  tracejob
  pbs_sleep
DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS
  pbs_ds_monitor
  pbs_idled
  pbs_probe
  pbs_upgrade_job
DESTINATION ${CMAKE_INSTALL_SBINDIR})