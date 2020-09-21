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

# include(OsRelease)

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
# find_package(Sendmail REQUIRED)
find_package(X11 REQUIRED)
find_package(OpenSSL REQUIRED)

find_library(MATH_LIBRARY m REQUIRED)


# set options
option(DISABLE_SHELL_PIPE "Disable use of pipe in job script name" OFF)
option(DISABLE_SYSLOG "Disable syslog support" OFF)
option(ENABLE_ALPS "Enable ALPS support" OFF)
option(ENABLE_PTL "Enable PTL" ON)

### set variables 
set(PBS_HOME_DIR /var/spool/pbs CACHE STRING "PBS home directory")
# FIXME: subst database_user
set(PBS_DATA_SERVICE_USER postgres CACHE STRING "PBS database user")
# FIXME: Do we need PBS_SERVER_FILE_NAME?
set(PBS_DATA_SERVICE_PORT 15007 CACHE STRING "PBS database port")
set(PBS_CONF_FILE /etc/pbs.conf CACHE STRING "PBS configuration file location")
set(TMP_DIR /var/tmp CACHE STRING "PBS temporary file location")
set(PBS_CORE_LIMIT unlimited CACHE STRING "PBS daemon coredump limit")
set(TCL_ATRSEP "." CACHE STRING "Tcl attribute separator")
set(SENDMAIL_CMD /usr/sbin/sendmail CACHE STRING "Full path to the sendmail executable")
set(XAUTH_BINARY xauth CACHE STRING "Name of the xauth executable")
set(MIN_STACK_LIMIT 0x1000000 CACHE STRING "Mininum stack limit")
if(NOT DISABLE_SHELL_PIPE)
	set(SHELL_INVOKE 1)
else()
	set(SHELL_INVOKE 0)
endif()
if(NOT DISABLE_SYSLOG)
	set(SYSLOG)
endif()
if(${Ical_VERSION_MAJOR} GREATER 1)
	set(LIBICAL_API2)
endif()
if(${UndoLR_FOUND})
	set(PBS_UNDOLR_ENABLED)
endif()
if(${ZLIB_FOUND})
	set(PBS_COMPRESSION_ENABLED)
endif()
# default install prefix
set(CMAKE_INSTALL_PREFIX /opt/pbs)
# if(${CMAKE_OS_ID} STREQUAL ubuntu OR ${CMAKE_OS_ID} STREQUAL debian)
# 	set(SYSTEMD_UNIT_DIR /lib/systemd/system)
# else()
# 	set(SYSTEMD_UNIT_DIR /usr/lib/systemd/system)
# endif()

# add the src subdirectory
add_subdirectory(src)
add_subdirectory(doc)