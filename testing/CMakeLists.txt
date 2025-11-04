cmake_minimum_required(VERSION 3.22.1)

project(stevensStringLibTest C CXX)

# ============================================================================
# Compiler Settings
# ============================================================================

# GoogleTest requires at least C++14, and stevensStringLib requires C++17
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================
# Build Options
# ============================================================================

option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)
option(ENABLE_SANITIZERS "Enable address and undefined behavior sanitizers" OFF)
option(BUILD_LEGACY_TESTS "Build legacy monolithic test file" ON)

# ============================================================================
# Add GoogleTest - Using FetchContent (no submodules needed!)
# ============================================================================

include(FetchContent)

message(STATUS "Fetching Google Test...")
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0  # Latest stable release
    GIT_SHALLOW    TRUE     # Only download latest commit
    FIND_PACKAGE_ARGS NAMES GTest
)

# Prevent GoogleTest from overriding compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GoogleTest available
FetchContent_MakeAvailable(googletest)

# Enable GoogleTest
enable_testing()
include(GoogleTest)

# ============================================================================
# Test Source Files - New Modular Structure
# ============================================================================

set(TEST_SOURCES
    unit/string_validation_test.cpp
    unit/string_manipulation_test.cpp
    unit/string_searching_test.cpp
    unit/string_conversion_test.cpp
    unit/property_based_test.cpp
)

# ============================================================================
# Create Test Executable
# ============================================================================

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    gtest_main
)

# ============================================================================
# Code Coverage Configuration
# ============================================================================

if(ENABLE_COVERAGE)
    message(STATUS "Code coverage enabled")

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            --coverage
            -fprofile-arcs
            -ftest-coverage
            -O0  # Disable optimizations for accurate coverage
            -g   # Include debug info
        )

        target_link_options(${PROJECT_NAME} PRIVATE
            --coverage
        )
    else()
        message(WARNING "Code coverage is only supported with GCC or Clang")
    endif()
endif()

# ============================================================================
# Sanitizers Configuration
# ============================================================================

if(ENABLE_SANITIZERS)
    message(STATUS "Sanitizers enabled (address, undefined behavior)")

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -fsanitize=address
            -fsanitize=undefined
            -fno-omit-frame-pointer
            -g
        )

        target_link_options(${PROJECT_NAME} PRIVATE
            -fsanitize=address
            -fsanitize=undefined
        )
    else()
        message(WARNING "Sanitizers are only supported with GCC or Clang")
    endif()
endif()

# ============================================================================
# Register Tests with CTest
# ============================================================================

gtest_discover_tests(${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTIES
        TIMEOUT 300
)

# ============================================================================
# Legacy Test Executable (Optional)
# ============================================================================

if(BUILD_LEGACY_TESTS)
    add_executable(${PROJECT_NAME}_legacy test.cpp)

    target_link_libraries(${PROJECT_NAME}_legacy PRIVATE
        gtest_main
    )

    # Apply same coverage/sanitizer settings
    if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME}_legacy PRIVATE --coverage -fprofile-arcs -ftest-coverage -O0 -g)
        target_link_options(${PROJECT_NAME}_legacy PRIVATE --coverage)
    endif()

    if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME}_legacy PRIVATE -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -g)
        target_link_options(${PROJECT_NAME}_legacy PRIVATE -fsanitize=address -fsanitize=undefined)
    endif()

    gtest_discover_tests(${PROJECT_NAME}_legacy
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

# ============================================================================
# Print Configuration Summary
# ============================================================================

message(STATUS "")
message(STATUS "=== Test Configuration Summary ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Code Coverage: ${ENABLE_COVERAGE}")
message(STATUS "Sanitizers: ${ENABLE_SANITIZERS}")
message(STATUS "Legacy Tests: ${BUILD_LEGACY_TESTS}")
message(STATUS "===================================")
message(STATUS "")
