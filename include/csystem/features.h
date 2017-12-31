#pragma once

#if (defined(__cplusplus) && __cplusplus >= 201703L) ||                        \
    (defined(_HAS_CXX17) && _HAS_CXX17 == 1) // fix for issue #464
#define CS_HAS_CPP_17
#define CS_HAS_CPP_14
#elif (defined(__cplusplus) && __cplusplus >= 201402L) ||                      \
    (defined(_HAS_CXX14) && _HAS_CXX14 == 1)
#define CS_HAS_CPP_14
#endif

/**
 * Determination a platform of an operation system
 * Fully supported supported only GNU GCC/G++, partially on Clang/LLVM
 */

#if defined(_WIN32)

#define CS_PLATFORM_NAME "windows" // Windows
#define CS_PLATFORM_WINDOWS
#elif defined(_WIN64)
#define CS_PLATFORM_NAME "windows" // Windows
#define CS_PLATFORM_WINDOWS
#elif defined(__CYGWIN__) && !defined(_WIN32)
#define CS_PLATFORM_NAME                                                       \
  "windows" // Windows (Cygwin POSIX under Microsoft Window)
#define CS_PLATFORM_WINDOWS

#elif defined(__linux__)
#define CS_PLATFORM_NAME                                                       \
  "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#define CS_PLATFORM_LINUX

#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
#include <sys/param.h>
#if defined(__hpux)
#define CS_PLATFORM_NAME "hp-ux" // HP-UX
#elif defined(_AIX)
#define CS_PLATFORM_NAME "aix" // IBM AIX

#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
#include <TargetConditionals.h>
#define CS_PLATFORM_DARWIN

#if TARGET_IPHONE_SIMULATOR == 1
#define CS_PLATFORM_NAME "ios" // Apple iOS
#elif TARGET_OS_IPHONE == 1
#define CS_PLATFORM_NAME "ios" // Apple iOS
#elif TARGET_OS_MAC == 1
#define CS_PLATFORM_NAME "osx" // Apple OSX
#endif

#elif defined(BSD)
#define CS_PLATFORM_NAME "bsd" // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
#define CS_PLATFORM_BSD
#endif
#elif defined(__sun) && defined(__SVR4)
#define CS_PLATFORM_NAME "solaris" // Oracle Solaris, Open Indiana
#define CS_PLATFORM_SOLARIS
#else
#define CS_PLATFORM_NAME NULL
#endif

#if defined(CS_PLATFORM_LINUX) || defined(CS_PLATFORM_DARWIN) ||               \
    defined(CS_PLATFORM_BSD)
#define CS_PLATFORM_UNIX
#endif

const char *const cs_CS_platform_name;
