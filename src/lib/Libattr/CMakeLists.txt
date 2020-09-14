function(gen_attrdef_file name)
	add_custom_command(OUTPUT ${name}.c
		COMMAND ${Python3_EXECUTABLE}
			${CMAKE_SOURCE_DIR}/buildutils/attr_parser.py
			-m ${CMAKE_CURRENT_SOURCE_DIR}/master_${name}.xml
			-s ${CMAKE_CURRENT_BINARY_DIR}/${name}.c
		MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/master_${name}.xml)
endfunction()
gen_attrdef_file(job_attr_def)
gen_attrdef_file(node_attr_def)
gen_attrdef_file(queue_attr_def)
gen_attrdef_file(resc_def_all)
gen_attrdef_file(resv_attr_def)
gen_attrdef_file(sched_attr_def)
gen_attrdef_file(svr_attr_def)

# parse xml attribute files into header files
function(gen_attrdef_header type)
  if (${type} STREQUAL "resc")
    # handle resc_def_all case since this one has irregular name
    add_custom_command(OUTPUT ${type}_def_enum.h
      COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/buildutils/attr_parser.py
        -m ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_${type}_def_all.xml
        -d ${CMAKE_CURRENT_BINARY_DIR}/${type}_def_enum.h
      MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_${type}_def_all.xml)
  else()
    add_custom_command(OUTPUT ${type}_attr_enum.h
      COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/buildutils/attr_parser.py
        -m ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_${type}_attr_def.xml
        -d ${CMAKE_CURRENT_BINARY_DIR}/${type}_attr_enum.h
      MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/src/lib/Libattr/master_${type}_attr_def.xml)
  endif()
endfunction()
gen_attrdef_header(job)
gen_attrdef_header(node)
gen_attrdef_header(queue)
gen_attrdef_header(resc)
gen_attrdef_header(resv)
gen_attrdef_header(sched)
gen_attrdef_header(svr)

set(LIBATTR_SOURCES 
  attr_atomic.c
  attr_fn_acl.c
  attr_fn_arst.c
  attr_fn_b.c
  attr_fn_c.c
  attr_fn_entlim.c
  attr_fn_f.c
  attr_fn_hold.c
  attr_fn_intr.c
  attr_fn_l.c
  attr_fn_ll.c
  attr_fn_resc.c
  attr_fn_size.c
  attr_fn_str.c
  attr_fn_time.c
  attr_fn_unkn.c
  attr_func.c
  attr_node_func.c
  attr_resc_func.c
  resc_map.c
  Long_.c
  LTostr.c
  strToL.c
  strTouL.c
  uLTostr.c
  job_attr_def.c
  node_attr_def.c
  queue_attr_def.c
  resc_def_all.c
  resv_attr_def.c
  sched_attr_def.c
  svr_attr_def.c
  resc_def_enum.h
  job_attr_enum.h
  node_attr_enum.h
  queue_attr_enum.h
  resv_attr_enum.h
  sched_attr_enum.h
  svr_attr_enum.h)
add_library(attr STATIC ${LIBATTR_SOURCES})
# add_dependencies(attr
#   resc_def_enum.h
#   job_attr_enum.h
#   node_attr_enum.h
#   queue_attr_enum.h
#   resv_attr_enum.h
#   sched_attr_enum.h
#   svr_attr_enum.h)
target_include_directories(attr PRIVATE
	${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
  ${CMAKE_CURRENT_BINARY_DIR})
