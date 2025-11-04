# Testing and Benchmarking Guide

This document describes the comprehensive testing and benchmarking infrastructure for stevensStringLib.

## Table of Contents

- [Quick Start](#quick-start)
- [Test Organization](#test-organization)
- [Running Tests](#running-tests)
- [Code Coverage](#code-coverage)
- [Benchmarking](#benchmarking)
- [Continuous Integration](#continuous-integration)
- [Best Practices](#best-practices)

---

## Quick Start

### Run All Tests

```bash
# Simple run
cd testing
./build.sh  # or use the script below

# With coverage
../scripts/run_tests.sh --coverage

# With sanitizers
../scripts/run_tests.sh --sanitizers
```

### Run Benchmarks

```bash
# Simple run
cd benchmarking
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cd build && make && ./stevensStringLibBenchmark

# Or use the script
../scripts/run_benchmarks.sh --format json
```

---

## Test Organization

Tests are organized into modular, focused files:

```
testing/
├── fixtures/
│   └── test_data.h              # Shared test data and fixtures
├── unit/
│   ├── string_validation_test.cpp    # isInteger, isFloat, isNumber
│   ├── string_manipulation_test.cpp  # separate, join, trim, reverse
│   ├── string_searching_test.cpp     # contains, find, startsWith
│   ├── string_conversion_test.cpp    # format, replace, mapify
│   └── property_based_test.cpp       # Randomized property tests
├── integration/                 # (Future: end-to-end tests)
└── test.cpp                     # Legacy monolithic test file
```

### Test Types

#### 1. **Unit Tests**

Individual function tests with comprehensive edge cases:

```cpp
TEST(Contains, SubstringExists_ReturnsTrue) {
    EXPECT_TRUE(contains("hello world", "world"));
}

TEST(Contains, EmptyString_ReturnsFalse) {
    EXPECT_FALSE(contains("", "test"));
}
```

#### 2. **Parameterized Tests**

Test same logic with multiple inputs:

```cpp
struct NumberTestCase {
    std::string input;
    bool is_integer;
    bool is_float;
};

class NumberValidationTest : public ::testing::TestWithParam<NumberTestCase> {};

TEST_P(NumberValidationTest, ValidatesCorrectly) {
    const auto& tc = GetParam();
    EXPECT_EQ(isInteger(tc.input), tc.is_integer);
    EXPECT_EQ(isFloat(tc.input), tc.is_float);
}

INSTANTIATE_TEST_SUITE_P(
    ComprehensiveTests,
    NumberValidationTest,
    ::testing::Values(
        NumberTestCase{"123", true, true},
        NumberTestCase{"123.5", false, true},
        NumberTestCase{"abc", false, false}
    )
);
```

#### 3. **Property-Based Tests**

Test mathematical properties that should always hold:

```cpp
TEST_F(PropertyTest, SeparateJoin_AreInverses) {
    for(int trial = 0; trial < 100; ++trial) {
        std::string original = join(randomParts(), ",");
        auto separated = separate(original, ',');
        std::string rejoined = join(separated, ",");

        EXPECT_EQ(original, rejoined);
    }
}
```

---

## Running Tests

### Using the Test Script (Recommended)

```bash
# Basic run
./scripts/run_tests.sh

# With code coverage
./scripts/run_tests.sh --coverage

# With sanitizers (detect memory issues)
./scripts/run_tests.sh --sanitizers

# Debug build with sanitizers
./scripts/run_tests.sh --debug --sanitizers

# Clean build
./scripts/run_tests.sh --clean --coverage
```

### Manual CMake Build

```bash
cd testing

# Configure
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Debug \
  -DENABLE_COVERAGE=ON \
  -DENABLE_SANITIZERS=OFF

# Build
cmake --build build -j$(nproc)

# Run
./build/stevensStringLibTest
```

### Running Specific Tests

```bash
# Run only validation tests
./build/stevensStringLibTest --gtest_filter="*Validation*"

# Run tests matching pattern
./build/stevensStringLibTest --gtest_filter="Contains*"

# List all tests
./build/stevensStringLibTest --gtest_list_tests

# Run with verbose output
./build/stevensStringLibTest --gtest_color=yes
```

---

## Code Coverage

### Generating Coverage Reports

```bash
# Use the script (easiest)
./scripts/run_tests.sh --coverage

# View report
xdg-open testing/build_test/coverage_report/index.html
```

### Manual Coverage Generation

```bash
cd testing

# Build with coverage
cmake -S . -B build -DENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Run tests
./build/stevensStringLibTest

# Generate report
cd build
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/googletest/*' -o coverage_filtered.info
genhtml coverage_filtered.info --output-directory coverage_report
```

### Coverage Targets

**Industry Standards:**
- **Line Coverage:** 80-90% (minimum 70%)
- **Branch Coverage:** 70-80% (minimum 60%)
- **Function Coverage:** 90%+ (all public functions)

**Current Status:**
- Run `./scripts/run_tests.sh --coverage` to see current coverage

---

## Benchmarking

### Benchmark Organization

Benchmarks are organized by function family:

```
benchmarking/
├── benchmarks/
│   ├── benchmark_separate.cpp    # Baseline, scaling, worst-case
│   ├── benchmark_join.cpp         # Performance comparisons
│   └── benchmark_validation.cpp   # Type checking benchmarks
├── fixtures/                      # Shared benchmark data
└── results/                       # Stored benchmark results
```

### Running Benchmarks

```bash
# Console output
./scripts/run_benchmarks.sh

# JSON output (for comparisons)
./scripts/run_benchmarks.sh --format json

# All formats
./scripts/run_benchmarks.sh --format all --repetitions 10

# With CPU performance mode (most accurate)
./scripts/run_benchmarks.sh --performance --format json
```

### Benchmark Types

#### 1. **Baseline Comparisons**

Compare against standard library:

```cpp
// Baseline: std::istringstream
static void BM_Separate_Baseline_IStringStream(benchmark::State& state) {
    // ... standard library implementation
}

// Our library
static void BM_Separate_Library(benchmark::State& state) {
    auto result = stevensStringLib::separate(input, ',');
    benchmark::DoNotOptimize(result);
}
```

#### 2. **Scaling Tests**

Measure how performance scales with input size:

```cpp
static void BM_Separate_Scaling(benchmark::State& state) {
    size_t num_elements = state.range(0);
    // ... generate input of size N

    for (auto _ : state) {
        auto result = stevensStringLib::separate(input, ',');
        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(num_elements);
}
BENCHMARK(BM_Separate_Scaling)
    ->Range(8, 8<<10)           // Test from 8 to 8192 elements
    ->Complexity(benchmark::oN); // Expected O(n) complexity
```

#### 3. **Worst-Case Scenarios**

```cpp
// No separators found
static void BM_Separate_WorstCase_NoSeparators(benchmark::State& state) {
    std::string input(state.range(0), 'a');  // Long string, no commas
    // ...
}

// Many empty elements
static void BM_Separate_WorstCase_ManySeparators(benchmark::State& state) {
    std::string input(state.range(0), ',');  // Just separators
    // ...
}
```

### Comparing Benchmark Results

```bash
# Run baseline
./scripts/run_benchmarks.sh --format json
cp benchmarking/results/benchmark_*.json benchmarking/baseline.json

# Make changes to code...

# Run current
./scripts/run_benchmarks.sh --format json

# Compare
./scripts/compare_benchmarks.py \
    benchmarking/baseline.json \
    benchmarking/results/benchmark_*.json
```

The comparison script will show:
- ✅ **Improvements:** Faster than baseline
- ⚠️ **Regressions:** Slower than baseline (fails CI)
- 📊 **New benchmarks:** Added benchmarks
- **Summary:** Overall performance change

---

## Continuous Integration

### GitHub Actions Workflow

The `.github/workflows/ci.yml` runs automatically on:
- Push to `main` or `develop` branches
- Pull requests

**Jobs:**

1. **Test Matrix:**
   - Compilers: GCC 11, Clang 14
   - Build types: Debug, Release
   - Runs all unit tests
   - Generates coverage (Debug builds)

2. **Sanitizers:**
   - AddressSanitizer (memory errors)
   - UndefinedBehaviorSanitizer (UB detection)

3. **Benchmarks:**
   - Runs performance benchmarks
   - Compares against baseline
   - Fails PR if regressions detected

4. **Code Quality:**
   - Checks for TODO comments
   - Validates line length
   - (Future: clang-format, clang-tidy)

5. **Documentation:**
   - Builds Doxygen documentation
   - Checks for warnings

### Viewing CI Results

1. Go to GitHub Actions tab
2. Click on your commit/PR
3. View individual job results
4. Download artifacts (coverage, benchmarks, docs)

---

## Best Practices

### Writing Tests

**DO:**
- ✅ Test edge cases (empty, null, overflow)
- ✅ Test both valid and invalid inputs
- ✅ Use descriptive test names
- ✅ Keep tests focused (one concept per test)
- ✅ Use test fixtures for shared setup

**DON'T:**
- ❌ Test implementation details
- ❌ Make tests depend on each other
- ❌ Use hard-coded values without explanation
- ❌ Write flaky tests (randomness without seed)

### Test Naming Convention

```cpp
// Pattern: FunctionName_Scenario_ExpectedBehavior
TEST(Contains, SubstringExists_ReturnsTrue) { ... }
TEST(Contains, EmptyString_ReturnsFalse) { ... }
TEST(Separate, NoSeparatorFound_ReturnsWholeString) { ... }
```

### Benchmark Best Practices

**DO:**
- ✅ Use `benchmark::DoNotOptimize()` on results
- ✅ Test at multiple scales (8, 64, 512, 4096)
- ✅ Include baseline comparisons
- ✅ Test worst-case scenarios
- ✅ Use `--repetitions` for statistical significance

**DON'T:**
- ❌ Include setup in benchmark loop
- ❌ Test only happy path
- ❌ Forget to disable CPU frequency scaling
- ❌ Compare Debug vs Release builds

### Coverage Best Practices

**Focus on:**
- ✅ All public API functions
- ✅ Edge case branches (empty, null, overflow)
- ✅ Error handling paths
- ✅ Loop boundary conditions

**Don't obsess over:**
- ❌ 100% coverage (unrealistic)
- ❌ Trivial getters/setters
- ❌ Code that can't be reached

---

## Troubleshooting

### Tests Fail to Build

```bash
# Clean and rebuild
rm -rf testing/build
./scripts/run_tests.sh --clean
```

### Coverage Not Generated

```bash
# Ensure lcov is installed
sudo apt-get install lcov

# Build must be Debug with coverage enabled
cmake -DENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
```

### Benchmarks Show High Variance

```bash
# Close other applications
# Disable CPU frequency scaling
./scripts/run_benchmarks.sh --performance

# Increase repetitions
./scripts/run_benchmarks.sh --repetitions 20
```

### Sanitizer Errors

```bash
# Run with verbose output
ASAN_OPTIONS=detect_leaks=1:check_initialization_order=1 \
UBSAN_OPTIONS=print_stacktrace=1 \
./build/stevensStringLibTest
```

---

## Additional Resources

- [Google Test Documentation](https://google.github.io/googletest/)
- [Google Benchmark Documentation](https://github.com/google/benchmark)
- [Coverage with lcov](https://github.com/linux-test-project/lcov)
- [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer)

---

## Contributing

When adding new functions:

1. ✅ Write unit tests in appropriate `unit/*.cpp` file
2. ✅ Add parameterized tests for edge cases
3. ✅ Write benchmarks in `benchmarking/benchmarks/`
4. ✅ Run `./scripts/run_tests.sh --coverage` (aim for 80%+)
5. ✅ Run `./scripts/run_benchmarks.sh` and verify no regressions
6. ✅ Update this documentation if needed

**Questions?** Open an issue on GitHub!
