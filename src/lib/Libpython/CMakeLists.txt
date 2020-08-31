add_custom_command(OUTPUT pbs_ifl.i
  COMMAND echo '%module pbs_ifl' > pbs_ifl.i
  COMMAND echo '%{' >> pbs_ifl.i
  COMMAND echo '\#include \"pbs_ifl.h\"' >> pbs_ifl.i
	COMMAND echo '%}' >> pbs_ifl.i
	COMMAND echo '%include \"pbs_ifl.h\"' >> pbs_ifl.i)

add_custom_command(OUTPUT pbs_ifl_wrap.c
	COMMAND ${SWIG_EXECUTABLE}
		-I${CMAKE_SOURCE_DIR}/include
		-I${CMAKE_BINARY_DIR}/include
		-I${SWIG_DIR} -I${SWIG_DIR}/python
		-python -outcurrentdir
		pbs_ifl.i
	DEPENDS pbs_ifl.i)

add_library(pbspython STATIC
	shared_python_utils.c
	common_python_utils.c
	pbs_python_external.c
	pbs_python_svr_external.c
	module_pbs_v1.c
	pbs_python_svr_internal.c
	pbs_python_svr_size_type.c
  pbs_python_import_types.c
  pbs_ifl_wrap.c)
target_include_directories(pbspython PRIVATE
  ${Python3_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include)
target_link_libraries(pbspython PRIVATE ${Python3_LIBRARIES})
set_target_properties(pbspython PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/pbs_ifl.py)

add_library(pbspython_svr STATIC
	shared_python_utils.c
	common_python_utils.c
	pbs_python_external.c
	pbs_python_svr_external.c
	module_pbs_v1.c
	pbs_python_svr_internal.c
	pbs_python_svr_size_type.c
  pbs_python_import_types.c
  pbs_ifl_wrap.c)
target_include_directories(pbspython_svr PRIVATE
  ${Python3_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
  ${CMAKE_SOURCE_DIR}/include
	${CMAKE_BINARY_DIR}/include)
target_link_libraries(pbspython_svr PRIVATE ${Python3_LIBRARIES})
target_compile_definitions(pbspython_svr PRIVATE LIBPYTHONSVR)
set_target_properties(pbspython_svr PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/pbs_ifl.py)