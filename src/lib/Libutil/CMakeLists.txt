set(UTIL_SOURCES
  get_hostname.c
  execvnode_seq_util.c
  pbs_ical.c
  misc_utils.c
  avltree.c
  hook.c
  work_task.c
  entlim.c
  daemon_protect.c
  pbs_array_list.c
  pbs_secrets.c
  pbs_aes_encrypt.c
  pbs_idx.c
)
if(${UndoLR_INCLUDE_DIR})
set(UTIL_SOURCES ${UTIL_SOURCES} undolr.c)
endif()

add_library(util ${UTIL_SOURCES})
target_include_directories(util
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_BINARY_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
    ${Ical_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/src/lib/Libattr
)
if(${UndoLR_INCLUDE_DIR})
target_include_directories(util PRIVATE ${UndoLR_INCLUDE_DIR})
endif()