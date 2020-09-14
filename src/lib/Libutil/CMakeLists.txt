if(${UndoLR_INCLUDE_DIR})
  list(APPEND EXTRA_SOURCES undolr.c)
  list(APPEND EXTRA_INCLUDES ${UndoLR_INCLUDE_DIR})
endif()
add_library(util
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
  ${EXTRA_SOURCES}
)
target_include_directories(util
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_BINARY_DIR}/src/include
    ${Ical_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/src/lib/Libattr
    ${EXTRA_INCLUDES}
)
