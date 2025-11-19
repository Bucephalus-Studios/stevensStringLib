# Building and Running Tests & Benchmarks

## Overview

The tests and benchmarks are split into multiple files for better organization:

**Tests** (in `testing/unit/`):
- `string_validation_test.cpp` - Validation functions (isInteger, isFloat, etc.)
- `string_manipulation_test.cpp` - Manipulation functions (reverse, scramble, wrapToWidth, etc.)
- `string_searching_test.cpp` - Search functions (contains, findAll, startsWith, etc.)
- `string_conversion_test.cpp` - Conversion functions (format, replaceSubstr, mapifyString, etc.)
- `property_based_test.cpp` - Property-based randomized tests

**Benchmarks** (in `benchmarking/benchmarks/`):
- `benchmark_separate.cpp` - Benchmarks for separate() function
- `benchmark_join.cpp` - Benchmarks for join() function
- `benchmark_validation.cpp` - Benchmarks for validation functions

CMake automatically compiles all these files into **single executables**:
- `Test` - All tests combined
- `Benchmark` - All benchmarks combined

## Building Tests

```bash
cd testing
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
```

This creates a single executable: `./Test`

## Running Tests

```bash
# From testing/build directory:
cd ..  # Go back to testing/ directory
./build/Test

# Or run specific test suites:
./build/Test --gtest_filter="WrapToWidth.*"
./build/Test --gtest_filter="Separate.*"

# List all tests:
./build/Test --gtest_list_tests
```

## Building Benchmarks

```bash
cd benchmarking
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
```

This creates a single executable: `./Benchmark`

## Running Benchmarks

```bash
# From benchmarking/build directory:
cd ..  # Go back to benchmarking/ directory
./build/Benchmark

# Run specific benchmarks:
./build/Benchmark --benchmark_filter="Separate_.*"
./build/Benchmark --benchmark_filter="Join_.*"

# List all benchmarks:
./build/Benchmark --benchmark_list_tests

# Save results to JSON:
./build/Benchmark --benchmark_out=results.json --benchmark_out_format=json
```

## Helper Scripts

For advanced usage, there are helper scripts in `scripts/`:

```bash
# Run tests with various options:
./scripts/run_tests.sh              # Basic test run
./scripts/run_tests.sh -c           # With coverage
./scripts/run_tests.sh -s           # With sanitizers
./scripts/run_tests.sh --clean -c   # Clean build with coverage

# Run benchmarks with various options:
./scripts/run_benchmarks.sh                    # Console output
./scripts/run_benchmarks.sh -f json            # JSON output
./scripts/run_benchmarks.sh -f all -r 10       # All formats, 10 repetitions
./scripts/run_benchmarks.sh -p                 # Performance CPU mode
```

## Test Options

CMake options for tests:
- `ENABLE_COVERAGE=ON` - Enable code coverage reporting
- `ENABLE_SANITIZERS=ON` - Enable address & undefined behavior sanitizers

Example:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON ..
```

## Key Points

✅ **All separate test files compile into ONE executable** (`Test`)
✅ **All separate benchmark files compile into ONE executable** (`Benchmark`)
✅ **CMake handles combining them** - you don't need to do anything special
✅ **Run from parent directory** (testing/ or benchmarking/) so tests can find data files
