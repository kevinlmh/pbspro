add_executable(mom_rcp
  extern.h
  pathnames.h
  pbs_stat.h
  rcp.c
  replace.c
  util.c)
target_include_directories(mom_rcp
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
)
install(TARGETS mom_rcp DESTINATION ${CMAKE_INSTALL_SBINDIR})