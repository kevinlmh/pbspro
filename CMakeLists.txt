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

# add .cmake dir to CMAKE_MODULE_PATH so we can use our own modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/.cmake)

# provides install directory variables as defined by the GNU Coding Standards
include(GNUInstallDirs)

# look for os id and os version from /etc/os-release
include(OsRelease)

# need these packages to build
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(SWIG REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(Editline REQUIRED)
find_package(EXPAT REQUIRED)
find_package(Ical REQUIRED)
find_package(ZLIB REQUIRED)
find_package(UndoLR QUIET)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(HwLoc REQUIRED)
find_package(TCL REQUIRED)
find_package(X11 REQUIRED)
find_package(OpenSSL REQUIRED)

find_library(MATH_LIBRARY m REQUIRED)
find_program(SENDMAIL_CMD NAMES sendmail PATHS /usr/sbin DOC "Full path to the sendmail executable" REQUIRED)

# set options
option(DISABLE_SHELL_PIPE "Disable use of pipe in job script name" OFF)
option(DISABLE_SYSLOG "Disable syslog support" OFF)
option(ENABLE_ALPS "Enable ALPS support" OFF)
option(ENABLE_PTL "Enable PTL" ON)
option(DEBUG "Enable build with -DDEBUG" OFF)

### set variables 
set(PBS_HOME_DIR /var/spool/pbs CACHE STRING "PBS home directory")
# FIXME: subst database_user
set(PBS_DATA_SERVICE_USER postgres CACHE STRING "PBS database user")
set(PBS_DAEMON_SERVICE_USER root CACHE STRING "PBS daemon service user")
# FIXME: Do we need PBS_SERVER_FILE_NAME?
set(PBS_DATA_SERVICE_PORT 15007 CACHE STRING "PBS database port")
set(PBS_CONF_FILE /etc/pbs.conf CACHE STRING "PBS configuration file location")
set(TMP_DIR /var/tmp CACHE STRING "PBS temporary file location")
set(PBS_CORE_LIMIT unlimited CACHE STRING "PBS daemon coredump limit")
set(TCL_ATRSEP "." CACHE STRING "Tcl attribute separator")
# set(SENDMAIL_CMD /usr/sbin/sendmail CACHE STRING "Full path to the sendmail executable")
set(XAUTH_BINARY xauth CACHE STRING "Name of the xauth executable")
set(MIN_STACK_LIMIT 0x1000000 CACHE STRING "Mininum stack limit")
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/opt/pbs" CACHE PATH "PBS installation prefix" FORCE)
endif()
set(CMAKE_BUILD_RPATH ${CMAKE_INSTALL_LIBDIR})
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_LIBDIR})

if(NOT DISABLE_SHELL_PIPE)
	set(SHELL_INVOKE 1)
else()
	set(SHELL_INVOKE 0)
endif()

if(NOT DISABLE_SYSLOG)
	set(SYSLOG 1)
else()
	set(SYSLOG 0)
endif()

message(STATUS "OS Id: "  ${CMAKE_OS_ID} ", OS Version: " ${CMAKE_OS_VERSION_ID})
if( (${CMAKE_OS_ID} STREQUAL suse AND ${CMAKE_OS_VERSION_ID} GREATER_EQUAL 1210) 
  OR (${CMAKE_OS_ID} STREQUAL rhel AND ${CMAKE_OS_VERSION_ID} GREATER_EQUAL 7)
  OR (${CMAKE_OS_ID} STREQUAL xdebian AND ${CMAKE_OS_VERSION_ID} GREATER_EQUAL 8)
  OR (${CMAKE_OS_ID} STREQUAL xubuntu AND ${CMAKE_OS_VERSION_ID} GREATER_EQUAL 16))
  set(HAVE_SYSTEMD 1)
endif()
if(${CMAKE_OS_ID} STREQUAL ubuntu OR ${CMAKE_OS_ID} STREQUAL debian)
	set(SYSTEMD_UNIT_DIR "/lib/systemd/system" CACHE PATH "Systemd unit directory")
else()
	set(SYSTEMD_UNIT_DIR "/usr/lib/systemd/system" CACHE PATH "Systemd unit directory")
endif()

# if(${DEBUG})
#   # cmake_compile_flags(-DDEBUG) set globally
# endif()

include(InstallRequiredSystemLibraries)

# packaging stuff
set(CPACK_PACKAGE_VENDOR "Altair Inc.")
set(CPACK_PACKAGE_VERSION_MAJOR "${PBS_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${PBS_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${PBS_PATCH_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_DESCRIPTION "OpenPBS descriotion")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Summary placeholder")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://www.openpbs.org")

set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/pbs") # or optionally, set CPACK_SET_DESTDIR to ON
set(CPACK_GENERATOR "RPM")

# src package specific variables
# CPACK_SOURCE_PACKAGE_FILE_NAME
# CPACK_SOURCE_STRIP_FILES
# CPACK_SOURCE_GENERATOR
# CPACK_SOURCE_OUTPUT_CONFIG_FILEError initializing the PBS dataservice
# CPACK_SOURCE_IGNORE_FILES

# RPM package specific variables
set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE ${CMAKE_BINARY_DIR}/rpm/server/pbs_server_postinstall)
set(CPACK_RPM_POST_TRANS_SCRIPT_FILE ${CMAKE_BINARY_DIR}/rpm/server/pbs_server_posttrans)
set(CPACK_RPM_PRE_UNINSTALL_SCRIPT_FILE ${CMAKE_BINARY_DIR}/rpm/server/pbs_server_preuninstall)

# DEB package specific variables 
# deb package requires a maintainer and contact info
# set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PBS team")
# set(CPACK_PACKAGE_CONTACT "pbspro@altair.com")

# add the src subdirectory
add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(rpm)


include(CPack)