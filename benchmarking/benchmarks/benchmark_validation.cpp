/**
 * @file benchmark_validation.cpp
 * @brief Benchmarks for validation functions
 */

#include <benchmark/benchmark.h>
#include <regex>
#include "../../stevensStringLib.h"

// ============================================================================
// BASELINE - Using std::regex
// ============================================================================

static void IsInteger_Baseline_Regex(benchmark::State& state) {
    std::string input = "123456";
    std::regex int_regex("^[+-]?[0-9]+$");

    for (auto _ : state) {
        bool result = std::regex_match(input, int_regex);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(IsInteger_Baseline_Regex);

// ============================================================================
// LIBRARY BENCHMARKS - isInteger
// ============================================================================

static void IsInteger_Library_Valid(benchmark::State& state) {
    std::string input = "123456";

    for (auto _ : state) {
        bool result = stevensStringLib::isInteger(input);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(IsInteger_Library_Valid);

static void IsInteger_Library_Invalid(benchmark::State& state) {
    std::string input = "123.456";

    for (auto _ : state) {
        bool result = stevensStringLib::isInteger(input);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(IsInteger_Library_Invalid);

// ============================================================================
// LIBRARY BENCHMARKS - isFloat
// ============================================================================

static void IsFloat_Library_Valid(benchmark::State& state) {
    std::string input = "123.456";

    for (auto _ : state) {
        bool result = stevensStringLib::isFloat(input);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(IsFloat_Library_Valid);

static void IsFloat_Library_Scientific(benchmark::State& state) {
    std::string input = "1.23e-10";

    for (auto _ : state) {
        bool result = stevensStringLib::isFloat(input);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(IsFloat_Library_Scientific);

// ============================================================================
// LIBRARY BENCHMARKS - isNumber
// ============================================================================

static void IsNumber_Library(benchmark::State& state) {
    std::string input = "123.456";

    for (auto _ : state) {
        bool result = stevensStringLib::isNumber(input);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(IsNumber_Library);

// ============================================================================
// SCALING - Input length impact
// ============================================================================

static void IsInteger_Scaling(benchmark::State& state) {
    size_t num_digits = state.range(0);
    std::string input(num_digits, '9');  // String of 9s

    for (auto _ : state) {
        bool result = stevensStringLib::isInteger(input);
        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(num_digits);
}
BENCHMARK(IsInteger_Scaling)
    ->RangeMultiplier(2)
    ->Range(1, 1<<10)
    ->Complexity();

// ============================================================================
// REAL WORLD - Mixed validation
// ============================================================================

static void Validation_MixedInputs(benchmark::State& state) {
    std::vector<std::string> inputs = {
        "123", "456.789", "1.23e10", "not_a_number",
        "-999", "0.0", "invalid", "42"
    };
    size_t idx = 0;

    for (auto _ : state) {
        auto& input = inputs[idx % inputs.size()];
        bool result = stevensStringLib::isNumber(input);
        benchmark::DoNotOptimize(result);
        ++idx;
    }
}
BENCHMARK(Validation_MixedInputs);
