add_executable(pbs_iff iff2.c ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c)
target_include_directories(pbs_iff
PRIVATE
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/lib/Libattr
)
target_link_libraries(pbs_iff
PRIVATE
  ${CMAKE_BINARY_DIR}/src/lib/Libpbs/libpbs_static.a
  ${CMAKE_BINARY_DIR}/src/lib/Libutil/libutil.a
  ${CMAKE_BINARY_DIR}/src/lib/Libnet/libnet.a
  ${CMAKE_BINARY_DIR}/src/lib/Libsec/libsec.a
  Threads::Threads
  ${ZLIB_LIBRARIES}
  dl
  # @socket_lib@
  # @KRB5_LIBS@
)

install(TARGETS pbs_iff DESTINATION ${CMAKE_INSTALL_SBINDIR})