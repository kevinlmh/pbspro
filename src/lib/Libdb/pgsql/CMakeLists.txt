add_library(db
  db_postgres.h
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
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
    ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(db PRIVATE ${PostgreSQL_LIBRARIES})