add_executable(pbs_rmget pbs_rmget.c)
target_include_directories(pbs_rmget
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
  ${ZLIB_INCLUDE_DIRS}
)
target_link_libraries(pbs_rmget
  ${CMAKE_BINARY_DIR}/src/lib/Libtpp/libtpp.a
  ${CMAKE_BINARY_DIR}/src/lib/Liblog/liblog.a
  ${CMAKE_BINARY_DIR}/src/lib/Libnet/libnet.a
  ${CMAKE_BINARY_DIR}/src/lib/Libpbs/libpbs_static.a
  ${CMAKE_BINARY_DIR}/src/lib/Libutil/libutil.a
  Threads::Threads
  ${ZLIB_LIBRARIES}
  ${CMAKE_DL_LIBS}
)

install(TARGETS pbs_rmget DESTINATION unsupported)
install(FILES
  pbs_loganalyzer
  pbs_stat
  pbs_config
  sgiICEvnode.sh
  sgiICEplacement.sh
  sgigenvnodelist.awk
  NodeHealthCheck.py
	load_balance.py
	mom_dyn_res.py
	rapid_inter.py
	run_pelog_shell.py
	NodeHealthCheck.json
	README
	pbs_jobs_at.8B
	pbs_rescquery.3B
	run_pelog_shell.ini
	cray_readme
	ReliableJobStartup.py
  pbs_output.py
  DESTINATION unsupported
)
