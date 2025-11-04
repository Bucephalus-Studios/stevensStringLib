# Quick Start Guide

Get up and running with stevensStringLib testing and benchmarking in 5 minutes.

## Prerequisites

```bash
# Install dependencies
sudo apt-get update
sudo apt-get install -y cmake g++ lcov python3
```

## Setup

```bash
# Clone the repository
git clone <your-repo-url>
cd stevensStringLib

# Dependencies (Google Test & Benchmark) are automatically downloaded by CMake!
# No submodule initialization needed - just build and run!
```

## Run Tests

```bash
# Simple test run
./scripts/run_tests.sh

# With coverage report
./scripts/run_tests.sh --coverage

# View coverage
xdg-open testing/build_test/coverage_report/index.html
```

## Run Benchmarks

```bash
# Console output
./scripts/run_benchmarks.sh

# JSON output for comparison
./scripts/run_benchmarks.sh --format json

# All formats
./scripts/run_benchmarks.sh --format all
```

## Project Structure

```
stevensStringLib/
├── stevensStringLib.h          # Main library (single header)
├── testing/                    # Test suite
│   ├── unit/                   # Modular test files
│   ├── fixtures/               # Shared test data
│   └── _deps/                  # Google Test (auto-downloaded by CMake)
├── benchmarking/              # Benchmark suite
│   ├── benchmarks/            # Modular benchmark files
│   └── _deps/                  # Google Benchmark (auto-downloaded)
├── scripts/                   # Automation scripts
│   ├── run_tests.sh          # Test runner
│   ├── run_benchmarks.sh     # Benchmark runner
│   └── compare_benchmarks.py # Comparison tool
└── .github/workflows/        # CI/CD configuration
```

## Common Commands

### Testing

```bash
# Run all tests
./scripts/run_tests.sh

# Run with sanitizers (detect memory issues)
./scripts/run_tests.sh --sanitizers

# Run specific test
cd testing/build
./stevensStringLibTest --gtest_filter="Contains*"

# List all tests
./stevensStringLibTest --gtest_list_tests
```

### Benchmarking

```bash
# Basic benchmark
./scripts/run_benchmarks.sh

# Save results for comparison
./scripts/run_benchmarks.sh --format json
cp benchmarking/results/benchmark_*.json benchmarking/baseline.json

# Compare after changes
./scripts/run_benchmarks.sh --format json
./scripts/compare_benchmarks.py \
    benchmarking/baseline.json \
    benchmarking/results/benchmark_*.json
```

### Development Workflow

```bash
# 1. Make changes to stevensStringLib.h

# 2. Run tests
./scripts/run_tests.sh --coverage

# 3. Check coverage (aim for 80%+)
xdg-open testing/build_test/coverage_report/index.html

# 4. Run benchmarks
./scripts/run_benchmarks.sh --format json

# 5. Compare performance
./scripts/compare_benchmarks.py baseline.json current.json

# 6. Commit if all pass
git add .
git commit -m "Your changes"
git push
```

## Test Organization

Tests are organized by function category:

- `string_validation_test.cpp` - isInteger, isFloat, isNumber
- `string_manipulation_test.cpp` - separate, join, trim, reverse
- `string_searching_test.cpp` - contains, find, startsWith
- `string_conversion_test.cpp` - format, replace, mapify
- `property_based_test.cpp` - Randomized property tests

## Benchmark Organization

Benchmarks compare against baselines:

- `benchmark_separate.cpp` - Baseline vs library, scaling, worst-case
- `benchmark_join.cpp` - Performance comparisons, roundtrip tests
- `benchmark_validation.cpp` - Type checking performance

## CI/CD

GitHub Actions automatically runs:
- ✅ Tests on GCC and Clang
- ✅ Coverage analysis
- ✅ Sanitizer checks
- ✅ Performance benchmarks
- ✅ Documentation build

View results: GitHub → Actions tab

## Troubleshooting

### "googletest not found"
This should not happen as CMake automatically downloads dependencies.
If you see this error:
```bash
# Clean and rebuild
cd testing
rm -rf build _deps
cmake -S . -B build
cmake --build build
```

### "lcov not found"
```bash
sudo apt-get install lcov
```

### High benchmark variance
```bash
# Use performance mode
./scripts/run_benchmarks.sh --performance --repetitions 10
```

### Test build fails
```bash
# Clean rebuild
cd testing
rm -rf build
./scripts/run_tests.sh --clean
```

## More Information

- **Full testing guide:** See `TESTING.md`
- **Implementation details:** See `IMPLEMENTATION_SUMMARY.md`
- **Library documentation:** See `README.md`

## Quick Reference

| Task | Command |
|------|---------|
| Run tests | `./scripts/run_tests.sh` |
| Run with coverage | `./scripts/run_tests.sh --coverage` |
| Run with sanitizers | `./scripts/run_tests.sh --sanitizers` |
| Run benchmarks | `./scripts/run_benchmarks.sh` |
| Compare benchmarks | `./scripts/compare_benchmarks.py old.json new.json` |
| Clean build | `./scripts/run_tests.sh --clean` |
| View coverage | `xdg-open testing/build_test/coverage_report/index.html` |

## Support

- 📖 Read `TESTING.md` for detailed documentation
- 🐛 Open GitHub issue for bugs
- 💡 Check CI logs for build errors
- 📧 Contact: See repository

---

**Now you're ready to develop with confidence!** 🎉
