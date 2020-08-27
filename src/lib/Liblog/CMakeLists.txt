set(LIBLOG_SOURCES pbs_log.c chk_file_sec.c log_event.c pbs_messages.c setup_env.c)
set(LIBLOG_XML_GENERATED )

add_library(log ${LIBLOG_SOURCES})

target_include_directories(log 
  PRIVATE
      ${CMAKE_SOURCE_DIR}/src/include
      ${CMAKE_BINARY_DIR}/src/include
      ${CMAKE_SOURCE_DIR}/include
      ${CMAKE_BINARY_DIR}/include
)