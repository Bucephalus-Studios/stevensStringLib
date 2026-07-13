cmake_minimum_required(VERSION 3.16)
project(stevensStringLib LANGUAGES CXX)

include(FetchContent)

# Header-only UTF-8 codec (encode/decode/validate against std::u32string) used by circularIndex()
# and other codepoint-aware string functions - see utf8ToUtf32()/utf32ToUtf8() in stevensStringLib.h.
FetchContent_Declare(utf8cpp
    GIT_REPOSITORY https://github.com/nemtrif/utfcpp.git
    GIT_TAG        v4.1.1
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(utf8cpp)

add_library(stevensStringLib INTERFACE)
add_library(stevensStringLib::stevensStringLib ALIAS stevensStringLib)

target_include_directories(stevensStringLib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(stevensStringLib INTERFACE cxx_std_17)
target_link_libraries(stevensStringLib INTERFACE utf8cpp)

option(STEVENSSTRINGLIB_BUILD_TESTS "Build tests" OFF)
option(STEVENSSTRINGLIB_BUILD_BENCHMARKS "Build benchmarks" OFF)

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
