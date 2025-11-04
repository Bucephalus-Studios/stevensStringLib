#!/bin/bash
# ==============================================================================
# run_tests.sh - Run stevensStringLib tests with various configurations
# ==============================================================================

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
BUILD_DIR="build_test"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
TEST_DIR="$PROJECT_ROOT/testing"

# Default options
ENABLE_COVERAGE=false
ENABLE_SANITIZERS=false
BUILD_TYPE="Release"
RUN_TESTS=true
CLEAN_BUILD=false

# ==============================================================================
# Functions
# ==============================================================================

print_header() {
    echo -e "${BLUE}============================================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}============================================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "${YELLOW}ℹ $1${NC}"
}

show_usage() {
    cat << EOF
Usage: $0 [OPTIONS]

Run stevensStringLib tests with various configurations.

OPTIONS:
    -c, --coverage          Enable code coverage reporting
    -s, --sanitizers        Enable address and undefined behavior sanitizers
    -d, --debug             Build in Debug mode (default: Release)
    -n, --no-run            Build but don't run tests
    --clean                 Clean build directory before building
    -h, --help              Show this help message

EXAMPLES:
    $0                      # Run tests in Release mode
    $0 -c                   # Run tests with coverage
    $0 -s                   # Run tests with sanitizers
    $0 -c --clean           # Clean build with coverage
    $0 -d -s                # Debug build with sanitizers

EOF
}

# ==============================================================================
# Parse command line arguments
# ==============================================================================

while [[ $# -gt 0 ]]; do
    case $1 in
        -c|--coverage)
            ENABLE_COVERAGE=true
            BUILD_TYPE="Debug"  # Coverage requires Debug build
            shift
            ;;
        -s|--sanitizers)
            ENABLE_SANITIZERS=true
            BUILD_TYPE="Debug"  # Sanitizers work best with Debug
            shift
            ;;
        -d|--debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        -n|--no-run)
            RUN_TESTS=false
            shift
            ;;
        --clean)
            CLEAN_BUILD=true
            shift
            ;;
        -h|--help)
            show_usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            show_usage
            exit 1
            ;;
    esac
done

# ==============================================================================
# Main script
# ==============================================================================

cd "$TEST_DIR"

print_header "stevensStringLib Test Suite"

echo "Configuration:"
echo "  Build Type: $BUILD_TYPE"
echo "  Coverage: $ENABLE_COVERAGE"
echo "  Sanitizers: $ENABLE_SANITIZERS"
echo "  Build Directory: $BUILD_DIR"
echo ""

# Clean if requested
if [ "$CLEAN_BUILD" = true ]; then
    print_info "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# ==============================================================================
# Configure with CMake
# ==============================================================================

print_header "Configuring with CMake"

CMAKE_FLAGS=(
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
)

if [ "$ENABLE_COVERAGE" = true ]; then
    CMAKE_FLAGS+=(-DENABLE_COVERAGE=ON)
fi

if [ "$ENABLE_SANITIZERS" = true ]; then
    CMAKE_FLAGS+=(-DENABLE_SANITIZERS=ON)
fi

cmake "${CMAKE_FLAGS[@]}" ..

if [ $? -ne 0 ]; then
    print_error "CMake configuration failed"
    exit 1
fi

print_success "CMake configuration successful"

# ==============================================================================
# Build
# ==============================================================================

print_header "Building tests"

make -j$(nproc)

if [ $? -ne 0 ]; then
    print_error "Build failed"
    exit 1
fi

print_success "Build successful"

# ==============================================================================
# Run tests
# ==============================================================================

if [ "$RUN_TESTS" = true ]; then
    print_header "Running tests"

    ./stevensStringLibTest --gtest_color=yes

    if [ $? -ne 0 ]; then
        print_error "Tests failed"
        exit 1
    fi

    print_success "All tests passed"
fi

# ==============================================================================
# Generate coverage report
# ==============================================================================

if [ "$ENABLE_COVERAGE" = true ] && [ "$RUN_TESTS" = true ]; then
    print_header "Generating coverage report"

    # Check if lcov is installed
    if ! command -v lcov &> /dev/null; then
        print_error "lcov not found. Install with: sudo apt-get install lcov"
        exit 1
    fi

    # Capture coverage data
    lcov --capture --directory . --output-file coverage.info

    # Remove external libraries from coverage
    lcov --remove coverage.info '/usr/*' '*/googletest/*' --output-file coverage_filtered.info

    # Generate HTML report
    genhtml coverage_filtered.info --output-directory coverage_report

    # Print summary
    echo ""
    print_header "Coverage Summary"
    lcov --list coverage_filtered.info

    print_success "Coverage report generated: $TEST_DIR/$BUILD_DIR/coverage_report/index.html"
fi

# ==============================================================================
# Summary
# ==============================================================================

echo ""
print_header "Test Summary"

if [ "$RUN_TESTS" = true ]; then
    print_success "All tests completed successfully"
else
    print_info "Tests built but not executed (use without -n to run)"
fi

if [ "$ENABLE_COVERAGE" = true ] && [ "$RUN_TESTS" = true ]; then
    echo ""
    print_info "To view coverage report:"
    echo "    xdg-open $TEST_DIR/$BUILD_DIR/coverage_report/index.html"
    echo "  or"
    echo "    firefox $TEST_DIR/$BUILD_DIR/coverage_report/index.html"
fi

echo ""
