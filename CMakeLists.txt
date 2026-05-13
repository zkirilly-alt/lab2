cmake_minimum_required(VERSION 3.16)
project(Lab2_DataStructures VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt6")

option(BUILD_TESTS "Build unit tests" OFF)
option(BUILD_QT "Build Qt GUI" ON)

if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()