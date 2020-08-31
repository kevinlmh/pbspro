add_library(sec cs_standard.c)
target_include_directories(sec
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_BINARY_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
)