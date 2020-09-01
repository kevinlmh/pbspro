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
)
target_include_directories(util
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_BINARY_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
    ${Ical_INCLUDES}
	  ${UndoLR_INCLUDES})
    # TODO:
    # @libical_inc@ \
    # @KRB5_CFLAGS@ \
    # @libundolr_inc@)

# TODO:
# if UNDOLR_ENABLED
# libutil_a_SOURCES += undolr.c
# endif