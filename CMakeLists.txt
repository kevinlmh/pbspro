# prefer newer version to old version of cmake
# because newer versions support more functionalities
# and cleaner syntax
cmake_minimum_required(VERSION 3.17)

# set PBS version
set(PBS_MAJOR_VERSION 2021)
set(PBS_MINOR_VERSION 1)
set(PBS_PATCH_VERSION 1)
set(PBS_VERSION ${PBS_MAJOR_VERSION}.${PBS_MINOR_VERSION}.${PBS_PATCH_VERSION} CACHE STRING "PBS Version")

# set the project name
project(openpbs VERSION ${PBS_VERSION} LANGUAGES C)

# need these packages to build
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(SWIG REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(EXPAT REQUIRED)
find_package(TCL REQUIRED)

# add the src subdirectory
add_subdirectory(include)
add_subdirectory(src)