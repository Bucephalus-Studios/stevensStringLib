cmake_minimum_required(VERSION 3.22.1)

project(Benchmark C CXX)

# ============================================================================
# Compiler Settings
# ============================================================================

# Google Benchmark and stevensStringLib require C++17
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================
# Build Options
# ============================================================================


# ============================================================================
# Add Google Benchmark - Using FetchContent (no submodules needed!)
# ============================================================================

include(FetchContent)

message(STATUS "Fetching Google Benchmark...")
FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        v1.8.3   # Latest stable release
    GIT_SHALLOW    TRUE     # Only download latest commit
    FIND_PACKAGE_ARGS NAMES benchmark
)

# Disable benchmark tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

# Make Google Benchmark available
FetchContent_MakeAvailable(googlebenchmark)

# ============================================================================
# Benchmark Source Files - New Modular Structure
# ============================================================================

set(BENCHMARK_SOURCES
    benchmarks/benchmark_separate.cpp
    benchmarks/benchmark_join.cpp
    benchmarks/benchmark_validation.cpp
)

# ============================================================================
# Create Benchmark Executable
# ============================================================================

add_executable(${PROJECT_NAME} ${BENCHMARK_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    benchmark::benchmark_main
)

# ============================================================================
# Optimization Flags for Release Builds
# ============================================================================

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -O3
            -march=native
            -DNDEBUG
        )
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        target_compile_options(${PROJECT_NAME} PRIVATE
            /O2
            /DNDEBUG
        )
    endif()
endif()


# ============================================================================
# Print Configuration Summary
# ============================================================================

message(STATUS "")
message(STATUS "=== Benchmark Configuration Summary ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "========================================")
message(STATUS "")
