cmake_minimum_required(VERSION 3.0)
project(csystem)


set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set (CSYSTEM_VERSION_MAJOR 0)
set (CSYSTEM_VERSION_MINOR 0)
set (CSYSTEM_VERSION_PATCH 3)

option(CS_EXAMPLE "build example" off)
option(CS_BUILD_SHARED "build shared" off)
option(CS_BUILD_CXX "build cxx version" off)
option(CS_BUILD_TEST "build tests" off)
option(CS_BUILD_CRYPTO "build crypto" off)
option(CS_BUILD_TERMINAL "build term" off)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(include)
add_subdirectory(src)

if(CS_BUILD_TEST)
    set(CS_BUILD_CRYPTO on)
endif(CS_BUILD_TEST)

if(CS_EXAMPLE)
    set(CS_BUILD_TERMINAL on)
endif(CS_EXAMPLE)


if((CS_BUILD_CRYPTO) OR (CS_BUILD_TEST))
    message(STATUS "Building csystem crypto")
    # if (APPLE AND CS_BUILD_SHARED)
    #     message("   CommonCrypto")
    #     set(CSYSTEM_CRYPTO_COMMONCRYPTO on)
    # else()
    #     message("   MbedTLS")
    #     set(CSYSTEM_CRYPTO_MBEDTLS on)
    #     option(ENABLE_PROGRAMS "Build mbed TLS programs." OFF)
    #     option(ENABLE_TESTING "Build mbed TLS tests." OFF)
    #     add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/mbedtls)
    # endif(APPLE AND CS_BUILD_SHARED) 

    if (APPLE)
        message("   CommonCrypto")
        set(CSYSTEM_CRYPTO_COMMONCRYPTO on)
    else()
        message("   MbedTLS")
        set(CSYSTEM_CRYPTO_MBEDTLS on)
        option(ENABLE_PROGRAMS "Build mbed TLS programs." OFF)
        option(ENABLE_TESTING "Build mbed TLS tests." OFF)
        add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/mbedtls)
    endif(APPLE) 

    
    add_subdirectory(src/crypto)
endif((CS_BUILD_CRYPTO) OR (CS_BUILD_TEST))


if (CS_BUILD_TERMINAL)
    add_subdirectory(src/terminal)
endif(CS_BUILD_TERMINAL)

if((CS_BUILD_CXX) OR (CS_EXAMPLE))
    set(CMAKE_CXX_STANDARD 14)
    add_subdirectory(cxx)
endif((CS_BUILD_CXX) OR (CS_EXAMPLE))

if(CS_EXAMPLE)
    add_subdirectory(example)
endif(CS_EXAMPLE)


# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

if(CS_BUILD_TEST)
	include(CTest)
	add_subdirectory(vendor/unity)
	add_subdirectory(test)
endif(CS_BUILD_TEST)

