
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
  dl
  nsl
)

add_executable(pbs_sleep pbs_sleep.c)
target_link_options(pbs_sleep -all-static)

add_executable(chk_tree chk_tree.c)
target_include_directories(chk_tree PRIVATE ${COMMON_INCLUDES})
target_link_libraries(chk_tree PRIVATE ${COMMON_LIBS})

add_executable(pbs_ds_monitor
  pbs_ds_monitor.c
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
)
target_include_directories(pbs_ds_monitor PRIVATE ${COMMON_INCLUDES})
# target_link_options(pbs_ds_monitor PRIVATE -Wl,-rpath,${CMAKE_INSTALL_LIBDIR})
target_link_libraries(pbs_ds_monitor
  ${COMMON_LIBS}
  ${CMAKE_BINARY_DIR}/src/lib/Libdb/libdb.so
  ${PostgreSQL_LIBRARIES}
  ssl
  crypto
)

add_executable(pbs_idled
  pbs_idled.c
  ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c
)
target_include_directories(pbs_idled
  PRIVATE
  ${X11_INCLUDE_DIR}
)
target_link_libraries(pbs_idled
  PRIVATE
  ${COMMON_LIBS}
  ${X11_LIBRARIES}
)

add_executable(pbs_hostn pbs_hostn.c)
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
)

add_executable(pbs_python
  ${CMAKE_BINARY_DIR}/src/lib/Libattr/job_attr_def.c
  ${CMAKE_BINARY_DIR}/src/lib/Libattr/node_attr_def.c
  ${CMAKE_BINARY_DIR}/src/lib/Libattr/queue_attr_def.c
  ${CMAKE_BINARY_DIR}/src/lib/Libattr/resc_def_all.c
  ${CMAKE_BINARY_DIR}/src/lib/Libattr/resv_attr_def.c
  ${CMAKE_BINARY_DIR}/src/lib/Libattr/svr_attr_def.c
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
)
target_link_libraries(pbs_python
  PRIVATE
  ${COMMON_LIBS}
  ${CMAKE_SOURCE_DIR}/src/lib/Libpython/libpbspython.a
	${CMAKE_SOURCE_DIR}/src/lib/Liblog/liblog.a
  ${CMAKE_SOURCE_DIR}/src/lib/Libattr/libattr.a
  ${Python3_LIBRARIES}
)
target_compile_definitions(pbs_python PRIVATE -DPBS_PYTHON=1.1)


