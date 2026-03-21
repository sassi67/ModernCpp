cmake_minimum_required(VERSION 4.2)

# if the environment variable VCPKG_ROOT is not set
# default to the local .vcpkg directory and clone vcpkg if it doesn't exist
if(NOT DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/.vcpkg)
else()
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
endif()

if(NOT EXISTS ${VCPKG_ROOT})
    message("Cloning vcpkg in ${VCPKG_ROOT}")
    execute_process(COMMAND git clone https://github.com/Microsoft/vcpkg.git ${VCPKG_ROOT})
else()
    # The following command has no effect if the vcpkg repository is in a detached head state.
    message("Auto-updating vcpkg in ${VCPKG_ROOT}")
    execute_process(COMMAND git pull WORKING_DIRECTORY ${VCPKG_ROOT})
endif()

if(NOT EXISTS ${VCPKG_ROOT}/README.md)
    message(FATAL_ERROR "***** FATAL ERROR: Could not clone vcpkg *****")
endif()

if(WIN32)
    set(VCPKG_EXEC ${VCPKG_ROOT}/vcpkg.exe)
    set(VCPKG_BOOTSTRAP ${VCPKG_ROOT}/bootstrap-vcpkg.bat)
else()
    set(VCPKG_EXEC ${VCPKG_ROOT}/vcpkg)
    set(VCPKG_BOOTSTRAP ${VCPKG_ROOT}/bootstrap-vcpkg.sh)
endif()

if(NOT EXISTS ${VCPKG_EXEC})
    message("Bootstrapping vcpkg in ${VCPKG_ROOT}")
    execute_process(COMMAND ${VCPKG_BOOTSTRAP} WORKING_DIRECTORY ${VCPKG_ROOT})
endif()

if(NOT EXISTS ${VCPKG_EXEC})
    message(FATAL_ERROR "***** FATAL ERROR: Could not bootstrap vcpkg *****")
endif()

if(WIN32)
    set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")
endif()

set(MODERNCPP_DEPENDENCIES 
    GTest:${VCPKG_TARGET_TRIPLET} 
    fmt:${VCPKG_TARGET_TRIPLET}
    spdlog:${VCPKG_TARGET_TRIPLET}
)

message(STATUS "***** Checking project third party dependencies in ${VCPKG_ROOT} *****")
execute_process(COMMAND ${VCPKG_EXEC} install ${MODERNCPP_DEPENDENCIES} WORKING_DIRECTORY ${VCPKG_ROOT})

project(ModernCppRoot LANGUAGES C CXX)

# Enforce C++20 for C++ targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GTest_DIR ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/share/gtest CACHE STRING "")
set(fmt_DIR ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/share/fmt CACHE STRING "")
set(spdlog_DIR ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/share/spdlog CACHE STRING "")

find_package(GTest CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)

