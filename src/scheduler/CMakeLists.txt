set(COMMON_LIBS
  sched
  ${CMAKE_BINARY_DIR}/src/lib/Libpbs/libpbs.a
  ${CMAKE_BINARY_DIR}/src/lib/Libtpp/libtpp.a
  ${CMAKE_BINARY_DIR}/src/lib/Libsec/libsec.a
  ${CMAKE_BINARY_DIR}/src/lib/Liblog/liblog.a
  ${CMAKE_BINARY_DIR}/src/lib/Libnet/libnet.a
  ${CMAKE_BINARY_DIR}/src/lib/Libutil/libutil.a
	${Python3_LIBRARIES}
	${Ical_LIBRARIES}
  ${ZLIB_LIBRARIES}
  Threads::Threads
  # @PYTHON_LDFLAGS@
  # @KRB5_LIBS@
)

set(COMMON_INC_DIRS 
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
  ${ZLIB_INCLUDE_DIRS}
  ${Python3_INCLUDE_DIRS}
)

add_library(sched STATIC
  ${CMAKE_SOURCE_DIR}/src/lib/Libpython/shared_python_utils.c
  buckets.c
  buckets.h
  check.c
  check.h
  config.h
  constant.h
  data_types.h
  dedtime.c
  dedtime.h
  fairshare.c
  fairshare.h
  fifo.c
  fifo.h
  get_4byte.c
  globals.c
  globals.h
  job_info.c
  job_info.h
  limits.c
  misc.c
  misc.h
  multi_threading.c
  multi_threading.h
  node_info.c
  node_info.h
  node_partition.c
  node_partition.h
  parse.c
  parse.h
  pbs_bitmap.c
  pbs_bitmap.h
  prev_job_info.c
  prev_job_info.h
  prime.c
  prime.h
  queue.c
  queue.h
  queue_info.c
  queue_info.h
  range.c
  range.h
  resource.h
  resource_resv.c
  resource_resv.h
  resv_info.c
  resv_info.h
  resource.c
  server_info.c
  server_info.h
  simulate.c
  simulate.h
  sort.c
  sort.h
  state_count.c
  state_count.h
  site_code.c
  site_code.h
  site_data.h)
target_include_directories(sched PRIVATE ${COMMON_INC_DIRS} ${CMAKE_BINARY_DIR}/src/lib/Libattr)
target_link_libraries(sched PRIVATE dl m)

add_executable(pbs_sched pbs_sched.c)
target_include_directories(pbs_sched PRIVATE ${COMMON_INC_DIRS} ${CMAKE_BINARY_DIR}/src/lib/Libattr)
target_link_libraries(pbs_sched PRIVATE PRIVATE ${COMMON_LIBS})
if(${PBS_UNDOLR_ENABLED})
  target_include_directories(pbs_sched PRIVATE ${UndoLR_INCLUDE_DIR})
endif()

add_executable(pbsfs pbsfs.c)
target_include_directories(pbsfs PRIVATE ${COMMON_INC_DIRS})
target_link_libraries(pbsfs PRIVATE ${COMMON_LIBS})

install(TARGETS sched DESTINATION lib)
install(TARGETS pbs_sched pbsfs DESTINATION sbin)