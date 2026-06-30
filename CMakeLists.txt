cmake_minimum_required(VERSION 3.16)
project(stevensStringLib LANGUAGES CXX)

add_library(stevensStringLib INTERFACE)
add_library(stevensStringLib::stevensStringLib ALIAS stevensStringLib)

target_include_directories(stevensStringLib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(stevensStringLib INTERFACE cxx_std_17)

option(STEVENSSTRINGLIB_BUILD_TESTS "Build tests" OFF)
option(STEVENSSTRINGLIB_BUILD_BENCHMARKS "Build benchmarks" OFF)

if(STEVENSSTRINGLIB_BUILD_TESTS OR STEVENSSTRINGLIB_BUILD_BENCHMARKS)
    include(FetchContent)
endif()

if(STEVENSSTRINGLIB_BUILD_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    add_subdirectory(testing)
endif()

if(STEVENSSTRINGLIB_BUILD_BENCHMARKS)
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.3
    )
    FetchContent_MakeAvailable(benchmark)
    add_subdirectory(benchmarking)
endif()
