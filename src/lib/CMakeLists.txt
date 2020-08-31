add_subdirectory(Libattr)
add_subdirectory(Liblog)
add_subdirectory(Libauth)
add_subdirectory(Libdb)
# CMAKETODO: cannot build because pbs_socklen_t is not defined
# it needs to be defined during configure
# search for it in the repo and look for a m4 file
#add_subdirectory(Libnet)
add_subdirectory(Libpython)
add_subdirectory(Libsec)
add_subdirectory(Libsite)
# CMAKETODO: MIN_STACK_LIMIT undefined
add_subdirectory(Libtpp)
add_subdirectory(Libpbs)