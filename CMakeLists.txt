#
# =============================================================================
# File: CMakeLists.txt
#
# Abstract:
#   Date        Description                              Developer
#   ----------  ---------------------------------------  -----------------
#   2026-03-28  Add GTest CTest integration              R. Vaughn
# =============================================================================
#

cmake_minimum_required(VERSION 3.14)

project(minesweeper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
    "Choose the type of build, options are: Debug, Release, RelWithDebInfo, MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if (NOT (WIN32))
    link_libraries(pthread)
endif()

# Game logic as a library so the test executable can link against it
add_library(minesweeper_lib STATIC
    src/colors.cpp
    src/common.cpp
    src/field.cpp
    src/game.cpp
    src/input.cpp
    src/print.cpp
    src/solver.cpp
    src/symbols.cpp
)
target_include_directories(minesweeper_lib PUBLIC include)

add_executable(minesweeper src/main.cpp)
target_link_libraries(minesweeper PRIVATE minesweeper_lib)

# Static linking and release-strip flags are scoped to the game executable only,
# so the test binary can link against the shared GTest DLL without conflicts.
if ((MINGW) OR (CYGWIN))
    target_link_options(minesweeper PRIVATE -static)
endif()

if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT (WIN32)) OR (CYGWIN) OR (MINGW)))
    target_link_options(minesweeper PRIVATE
        $<$<CONFIG:Release>:-s>
        $<$<CONFIG:Release>:-Wl,--gc-sections>
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND (WIN32) AND (NOT (MSVC)))
    target_link_options(minesweeper PRIVATE $<$<CONFIG:Release>:-Wl>)
endif()

install(TARGETS minesweeper RUNTIME DESTINATION bin)

# Unit tests — GTest is fetched and built from source to guarantee the same
# compiler and C runtime are used as the rest of the project.
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL      https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    # Keep GTest's CRT choice in sync with our project (required on Windows)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    # Don't build GMock or install GTest alongside the project
    set(BUILD_GMOCK  OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()
