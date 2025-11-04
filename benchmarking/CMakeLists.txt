cmake_minimum_required(VERSION 3.22.1)

project(stevensStringLibBenchmark C CXX)

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

option(BUILD_LEGACY_BENCHMARKS "Build legacy monolithic benchmark file" ON)

# ============================================================================
# Add Google Benchmark
# ============================================================================

add_subdirectory(googlebenchmark)

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
    benchmark::benchmark
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
# Legacy Benchmark Executable (Optional)
# ============================================================================

if(BUILD_LEGACY_BENCHMARKS)
    add_executable(${PROJECT_NAME}_legacy benchmark.cpp)

    target_link_libraries(${PROJECT_NAME}_legacy PRIVATE
        benchmark::benchmark
    )

    # Apply same optimization flags
    if(CMAKE_BUILD_TYPE STREQUAL "Release" AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME}_legacy PRIVATE -O3 -march=native -DNDEBUG)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release" AND CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        target_compile_options(${PROJECT_NAME}_legacy PRIVATE /O2 /DNDEBUG)
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
message(STATUS "Legacy Benchmarks: ${BUILD_LEGACY_BENCHMARKS}")
message(STATUS "========================================")
message(STATUS "")
