cmake_minimum_required(VERSION 3.0)
project(csystem)


set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set (CSYSTEM_VERSION_MAJOR 0)
set (CSYSTEM_VERSION_MINOR 0)
set (CSYSTEM_VERSION_PATCH 2)

option(CS_EXAMPLE "build example" off)
option(CS_BUILD_SHARED "build shared" off)
option(CS_BUILD_CXX "build cxx version" off)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(include)
add_subdirectory(src)


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


