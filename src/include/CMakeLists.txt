include(CheckIncludeFile)
include(CheckTypeSize)
include(CheckSymbolExists)
include(CheckCSourceCompiles)

string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} PBS_MACH)
set(PBS_MACH ${PBS_MACH} CACHE STRING "")

check_include_file(sys/eventfd.h HAVE_SYS_EVENTFD_H)
check_include_file(sys/ioctl.h HAVE_SYS_IOCTL_H)
check_symbol_exists(h_errno "netdb.h" H_ERRNO_DECLARED)
set(CMAKE_EXTRA_INCLUDE_FILES "sys/socket.h")
set(CMAKE_REQUIRED_DEFINITIONS -D_GNU_SOURCE)
check_type_size(socklen_t HAVE_SOCKLEN_T)

# check_c_source_compiles("
# #include <sys/epoll.h>
# int main()
# {
#   return ((epoll_create(100) == -1) ? -1 : 0);
# }
# " PBS_HAVE_EPOLL)

# check_c_source_compiles("
# #include <unistd.h>
# #include <poll.h>
# #include <signal.h>
# #include <stdio.h>
# #include <errno.h>
# #include <sys/epoll.h>
# int main()
# {
#   sigset_t allsigs;
#   int n;
#   int maxevents = 1;
#   int timeout = 0;
#   int epollfd;
#   struct   epoll_event  events;
#   sigemptyset(&allsigs);
#   events.events = EPOLLIN;
#   epollfd = epoll_create1(0);
#   if (epollfd == -1) {
#     perror(\"epoll_create1\");
#     return (1);
#   }
#   n = epoll_pwait(epollfd, &events, maxevents, timeout, &allsigs);
#   return (n);
# }
# " PBS_HAVE_EPOLL_PWAIT)

# check_c_source_compiles("
# #include <unistd.h>
# #include <poll.h>
# #include <signal.h>
# int main()
# {
#   sigset_t allsigs;
#   int n;
#   int fd[2];
#   struct timespec timeoutspec;
#   struct   pollfd  pollfds[1];
#   timeoutspec.tv_nsec = 1000;
#   timeoutspec.tv_sec = 0;
#   pipe(fd);
#   pollfds[0].fd = fd[0];
#   sigemptyset(&allsigs);
#   n = ppoll(pollfds, 1, &timeoutspec, &allsigs);
#   return (n);
# }" PBS_HAVE_PPOLL)

# # HAVE_GETPWUID HAVE_INITGROUPS HAVE_SETEUID HAVE_SETEGID HAVE_SETRESUID HAVE_SETRESGID
# check_c_source_compiles("
# #include <pwd.h>
# int main() {
#   struct passwd *pwd = getpwuid(getuid());
# }" HAVE_GETPWUID)

# check_c_source_compiles("
# #include <unistd.h>
# int main() {
#   initgroups(\"root\", 0);
# }" HAVE_INITGROUPS)

# check_c_source_compiles("
# #include <unistd.h>
# int main() {
#   setuid(1);
# }" HAVE_SETEUID)

# check_c_source_compiles("
# #include <unistd.h>
# int main() {
#   setgid(1);
# }" HAVE_SETEGID)

# check_c_source_compiles("
# #include <unistd.h>
# int main() {
#   setresuid(-1, -1, -1);
# }" HAVE_SETRESUID)

# check_c_source_compiles("
# #include <unistd.h>
# int main() {
#   setresgid(-1, -1, -1);
# }" HAVE_SETRESGID)

check_symbol_exists(epoll_create sys/epoll.h PBS_HAVE_EPOLL)
check_symbol_exists(epoll_pwait sys/epoll.h PBS_HAVE_EPOLL_PWAIT)
check_symbol_exists(ppoll poll.h PBS_HAVE_PPOLL)
# HAVE_GETPWUID HAVE_INITGROUPS HAVE_SETEUID HAVE_SETEGID HAVE_SETRESUID HAVE_SETRESGID
check_symbol_exists(getpwuid pwd.h HAVE_GETPWUID)
check_symbol_exists(initgroups grp.h HAVE_INITGROUPS)
check_symbol_exists(seteuid unistd.h HAVE_SETEUID)
check_symbol_exists(setegid unistd.h HAVE_SETEGID)
check_symbol_exists(setresuid unistd.h HAVE_SETRESUID)
check_symbol_exists(setresgid unistd.h HAVE_SETRESGID)

configure_file(pbs_config.h.in pbs_config.h)
configure_file(pbs_version.h.in pbs_version.h)

install(FILES pbs_error.h pbs_ifl.h rm.h tm.h tm_.h DESTINATION include)