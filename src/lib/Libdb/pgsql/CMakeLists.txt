add_library(db SHARED
  db_common.c
  db_attr.c
  db_job.c
  db_resv.c
  db_svr.c
  db_que.c
  db_node.c
  db_sched.c)
target_include_directories(db
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_BINARY_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(db
  PRIVATE
  ${PostgreSQL_LIBRARIES}
)
# need to link to libpbs and libnet
install(TARGETS db DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(PROGRAMS
  pbs_db_utility
  pbs_db_env
  pbs_db_schema.sql
  pbs_schema_upgrade
  DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)