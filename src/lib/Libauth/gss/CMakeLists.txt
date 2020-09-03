add_library(auth_gss pbs_gss.c)
target_include_directories(auth_gss PRIVATE
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include)
target_link_libraries(auth_gss Threads::Threads)