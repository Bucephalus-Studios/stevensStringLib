#!/bin/bash
# ==============================================================================
# run_benchmarks.sh - Run stevensStringLib benchmarks
# ==============================================================================

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
BUILD_DIR="build_benchmark"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BENCHMARK_DIR="$PROJECT_ROOT/benchmarking"
RESULTS_DIR="$BENCHMARK_DIR/results"
TIMESTAMP=$(date +%Y%m%d_%H%M%S)

# Default options
OUTPUT_FORMAT="console"
REPETITIONS=5
CLEAN_BUILD=false
SET_PERFORMANCE_MODE=false

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

Run stevensStringLib benchmarks with various output formats.

OPTIONS:
    -f, --format FORMAT     Output format: console, json, csv, all (default: console)
    -r, --repetitions N     Number of repetitions (default: 5)
    -p, --performance       Set CPU to performance mode (requires sudo)
    --clean                 Clean build directory before building
    -h, --help              Show this help message

OUTPUT FORMATS:
    console     Human-readable console output with colors
    json        JSON format for comparison tools
    csv         CSV format for spreadsheet analysis
    all         Generate all formats

EXAMPLES:
    $0                              # Run with console output
    $0 -f json                      # Generate JSON for comparisons
    $0 -f all -r 10                 # All formats, 10 repetitions
    $0 -p                           # Use performance CPU mode
    $0 --clean -f json              # Clean build and JSON output

NOTE:
    Benchmarks are most accurate when:
    - System is not under heavy load
    - CPU frequency scaling is disabled (-p option)
    - Running in Release mode with optimizations

EOF
}

set_cpu_performance_mode() {
    if [ "$SET_PERFORMANCE_MODE" = true ]; then
        print_info "Setting CPU to performance mode (requires sudo)..."

        if command -v cpupower &> /dev/null; then
            sudo cpupower frequency-set --governor performance 2>/dev/null || {
                print_error "Failed to set CPU performance mode"
                print_info "Continuing without performance mode..."
            }
        else
            print_info "cpupower not found, skipping performance mode"
            print_info "Install with: sudo apt-get install linux-tools-common"
        fi
    fi
}

reset_cpu_mode() {
    if [ "$SET_PERFORMANCE_MODE" = true ]; then
        if command -v cpupower &> /dev/null; then
            print_info "Resetting CPU to powersave mode..."
            sudo cpupower frequency-set --governor powersave 2>/dev/null || true
        fi
    fi
}

# ==============================================================================
# Parse command line arguments
# ==============================================================================

while [[ $# -gt 0 ]]; do
    case $1 in
        -f|--format)
            OUTPUT_FORMAT="$2"
            shift 2
            ;;
        -r|--repetitions)
            REPETITIONS="$2"
            shift 2
            ;;
        -p|--performance)
            SET_PERFORMANCE_MODE=true
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

# Trap to ensure CPU mode is reset
trap reset_cpu_mode EXIT

# ==============================================================================
# Main script
# ==============================================================================

cd "$BENCHMARK_DIR"

print_header "stevensStringLib Benchmark Suite"

echo "Configuration:"
echo "  Output Format: $OUTPUT_FORMAT"
echo "  Repetitions: $REPETITIONS"
echo "  Performance Mode: $SET_PERFORMANCE_MODE"
echo "  Build Directory: $BUILD_DIR"
echo ""

# Set CPU performance mode if requested
set_cpu_performance_mode

# Clean if requested
if [ "$CLEAN_BUILD" = true ]; then
    print_info "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create build and results directories
mkdir -p "$BUILD_DIR"
mkdir -p "$RESULTS_DIR"
cd "$BUILD_DIR"

# ==============================================================================
# Configure with CMake
# ==============================================================================

print_header "Configuring with CMake"

cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS="-O3 -march=native" \
      ..

if [ $? -ne 0 ]; then
    print_error "CMake configuration failed"
    exit 1
fi

print_success "CMake configuration successful"

# ==============================================================================
# Build
# ==============================================================================

print_header "Building benchmarks"

make -j$(nproc)

if [ $? -ne 0 ]; then
    print_error "Build failed"
    exit 1
fi

print_success "Build successful"

# ==============================================================================
# Run benchmarks
# ==============================================================================

BENCHMARK_FLAGS=(
    --benchmark_repetitions="$REPETITIONS"
    --benchmark_report_aggregates_only=true
)

case $OUTPUT_FORMAT in
    console)
        print_header "Running benchmarks (console output)"
        ./stevensStringLibBenchmark "${BENCHMARK_FLAGS[@]}" --benchmark_color=true
        ;;

    json)
        print_header "Running benchmarks (JSON output)"
        OUTPUT_FILE="$RESULTS_DIR/benchmark_${TIMESTAMP}.json"
        ./stevensStringLibBenchmark "${BENCHMARK_FLAGS[@]}" \
            --benchmark_out="$OUTPUT_FILE" \
            --benchmark_out_format=json \
            --benchmark_color=true

        print_success "JSON results saved to: $OUTPUT_FILE"
        ;;

    csv)
        print_header "Running benchmarks (CSV output)"
        OUTPUT_FILE="$RESULTS_DIR/benchmark_${TIMESTAMP}.csv"
        ./stevensStringLibBenchmark "${BENCHMARK_FLAGS[@]}" \
            --benchmark_out="$OUTPUT_FILE" \
            --benchmark_out_format=csv \
            --benchmark_color=true

        print_success "CSV results saved to: $OUTPUT_FILE"
        ;;

    all)
        print_header "Running benchmarks (all formats)"

        # Console
        print_info "Console output:"
        ./stevensStringLibBenchmark "${BENCHMARK_FLAGS[@]}" --benchmark_color=true

        # JSON
        JSON_FILE="$RESULTS_DIR/benchmark_${TIMESTAMP}.json"
        print_info "Generating JSON..."
        ./stevensStringLibBenchmark "${BENCHMARK_FLAGS[@]}" \
            --benchmark_out="$JSON_FILE" \
            --benchmark_out_format=json > /dev/null 2>&1

        # CSV
        CSV_FILE="$RESULTS_DIR/benchmark_${TIMESTAMP}.csv"
        print_info "Generating CSV..."
        ./stevensStringLibBenchmark "${BENCHMARK_FLAGS[@]}" \
            --benchmark_out="$CSV_FILE" \
            --benchmark_out_format=csv > /dev/null 2>&1

        print_success "Results saved:"
        echo "  JSON: $JSON_FILE"
        echo "  CSV:  $CSV_FILE"
        ;;

    *)
        print_error "Unknown format: $OUTPUT_FORMAT"
        show_usage
        exit 1
        ;;
esac

# ==============================================================================
# Summary
# ==============================================================================

echo ""
print_header "Benchmark Summary"

print_success "Benchmarks completed successfully"

if [ "$OUTPUT_FORMAT" != "console" ]; then
    print_info "Results saved in: $RESULTS_DIR/"
fi

echo ""
print_info "System information:"
echo "  $(uname -s) $(uname -r)"
echo "  $(lscpu | grep "Model name" | cut -d':' -f2 | xargs)"
echo "  Build type: Release with -O3 -march=native"

if [ "$SET_PERFORMANCE_MODE" = true ]; then
    print_info "CPU performance mode was used for these benchmarks"
fi

echo ""
