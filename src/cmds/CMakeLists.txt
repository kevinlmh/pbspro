# add subdirectories
add_subdirectory(scripts)

# CMAKETODO: fix find socket lib
set(COMMON_LIBS
  ${CMAKE_BINARY_DIR}/src/lib/Libpbs/libpbs.a
  ${CMAKE_BINARY_DIR}/src/lib/Libnet/libnet.a
  ${CMAKE_BINARY_DIR}/src/lib/Libsec/libsec.a
  ${CMAKE_BINARY_DIR}/src/lib/Libutil/libutil.a
  Threads::Threads dl nsl)
set(COMMON_SOURCES ${CMAKE_SOURCE_DIR}/src/lib/Libcmds/cmds_common.c)

# function for adding cmd with common sources and 
# link to common libs, for cmds that have more than
# one source file or more link targets please add
# them manually
function(add_cmd name)
  add_executable(${name} ${name}.c ${COMMON_SOURCES})
  target_include_directories(${name}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_BINARY_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include)
  target_link_libraries(${name} ${COMMON_LIBS})
endfunction()

# bin programs
add_cmd(pbsdsh pbsdsh.c)
add_cmd(pbsnodes pbsnodes.c)
add_cmd(pbs_attach pbs_attach.c)
add_cmd(pbs_tmrsh pbs_tmrsh.c)
add_cmd(pbs_ralter pbs_ralter.c)
add_cmd(pbs_rdel pbs_rdel.c)
add_cmd(pbs_rstat pbs_rstat.c)
add_cmd(pbs_rsub pbs_rsub.c)
add_cmd(pbs_release_nodes pbs_release_nodes.c)
add_cmd(qalter qalter.c)
add_cmd(qdel qdel.c)
add_cmd(qdisable qdisable.c)
add_cmd(qenable qenable.c)
add_cmd(qhold qhold.c)
add_cmd(qmove qmove.c)
add_cmd(qorder qorder.c)
add_cmd(qmsg qmsg.c)
add_cmd(qrerun qrerun.c)
add_cmd(qrls qrls.c)
add_cmd(qrun qrun.c)
add_cmd(qselect qselect.c)
add_cmd(qsig qsig.c)
add_cmd(qstat qstat.c)
add_cmd(qstart qstart.c)
add_cmd(qstop qstop.c)
add_cmd(qsub qsub.c)
add_cmd(qterm qterm.c)
add_executable(qmgr qmgr.c qmgr_sup.c ${COMMON_SOURCES})
target_include_directories(qmgr
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_BINARY_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
    ${Editline_INCLUDE_DIR})
target_link_libraries(qmgr ${COMMON_LIBS} ${Editline_LIBRARIES})

# sbin programs
add_executable(pbs_demux pbs_demux.c)
target_include_directories(pbs_demux
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include)
target_link_libraries(pbs_demux ${COMMON_LIBS})

# CMAKETODO: undefined reference to get_hostaddress
# add_executable(pbs_dataservice pbs_dataservice.c ${COMMON_SOURCES})
# target_include_directories(pbs_dataservice
#   PRIVATE
#     ${CMAKE_SOURCE_DIR}/src/include
#     ${CMAKE_BINARY_DIR}/src/include
#     ${CMAKE_SOURCE_DIR}/include
#     ${CMAKE_BINARY_DIR}/include
#     ${PostgreSQL_INCLUDE_DIRS})
# target_link_libraries(pbs_dataservice
#   ${COMMON_LIBS}
#   ${PostgreSQL_LIBRARIES}
#   ${CMAKE_BINARY_DIR}/src/lib/Libdb/pgsql/libdb.a
#   ssl
#   crypto)

# add_executable(pbs_ds_password pbs_ds_password.c ${COMMON_SOURCES})
# target_include_directories(pbs_ds_password
#   PRIVATE
#     ${CMAKE_SOURCE_DIR}/src/include
#     ${CMAKE_BINARY_DIR}/src/include
#     ${CMAKE_SOURCE_DIR}/include
#     ${CMAKE_BINARY_DIR}/include
#     ${PostgreSQL_INCLUDE_DIRS})
# target_link_libraries(pbs_ds_password
#   ${COMMON_LIBS}
#   ${PostgreSQL_LIBRARIES}
#   ${CMAKE_BINARY_DIR}/src/lib/Libdb/pgsql/libdb.a
#   ssl
#   crypto)


# dist bin programs
# these do not need to compile, only configure and install
configure_file(mpiexec.in mpiexec @ONLY)
configure_file(nqs2pbs.in nqs2pbs @ONLY)
configure_file(pbs_lamboot.in pbs_lamboot @ONLY)
configure_file(pbs_mpihp.in pbs_mpihp @ONLY)
configure_file(pbs_mpilam.in pbs_mpiam @ONLY)
configure_file(pbs_mpirun.in pbs_mpirun @ONLY)
configure_file(pbs_remsh.in pbs_remsh @ONLY)
configure_file(pbsrun.in pbsrun @ONLY)
configure_file(pbsrun_unwrap.in pbsrun_unwrap @ONLY)
configure_file(pbsrun_wrap.in pbsrun_wrap @ONLY)
