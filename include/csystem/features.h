#pragma once

#if (defined(__cplusplus) && __cplusplus >= 201703L) ||                        \
    (defined(_HAS_CXX17) && _HAS_CXX17 == 1) // fix for issue #464
#define BP_HAS_CPP_17
#define BP_HAS_CPP_14
#elif (defined(__cplusplus) && __cplusplus >= 201402L) ||                      \
    (defined(_HAS_CXX14) && _HAS_CXX14 == 1)
#define BP_HAS_CPP_14
#endif

/**
 * Determination a platform of an operation system
 * Fully supported supported only GNU GCC/G++, partially on Clang/LLVM
 */

#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#define PLATFORM_WINDOWS
#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // Windows
#define PLATFORM_WINDOWS
#elif defined(__CYGWIN__) && !defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
#define PLATFORM_WINDOWS
#elif defined(__linux__)
#define PLATFORM_NAME                                                          \
  "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#define PLATFORM_LINUX
#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
#include <sys/param.h>
#if defined(__hpux)
#define PLATFORM_NAME "hp-ux" // HP-UX
#elif defined(_AIX)
#define PLATFORM_NAME "aix"                   // IBM AIX
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
#define PLATFORM_NAME "ios" // Apple iOS
#define PLATFORM__DARWIN
#elif TARGET_OS_IPHONE == 1
#define PLATFORM_NAME "ios" // Apple iOS
#define PLATFORM_DARWIN
#elif TARGET_OS_MAC == 1
#define PLATFORM_NAME "osx" // Apple OSX
#define PLATFORM_DARWIN
#endif
#elif defined(BSD)
#define PLATFORM_NAME "bsd" // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
#endif
#elif defined(__sun) && defined(__SVR4)
#define PLATFORM_NAME "solaris" // Oracle Solaris, Open Indiana
#else
#define PLATFORM_NAME NULL
#endif

#if defined(PLATFORM_LINUX) || defined(PLATFORM_DARWIN)
#define PLATFORM_UNIX
#endif