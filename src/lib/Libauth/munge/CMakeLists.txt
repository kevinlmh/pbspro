add_library(auth_munge munge_supp.c)
target_include_directories(auth_munge PRIVATE
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/src/include
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include)
