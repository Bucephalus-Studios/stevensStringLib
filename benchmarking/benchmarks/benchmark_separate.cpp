/**
 * @file benchmark_separate.cpp
 * @brief Comprehensive benchmarks for separate() function
 *
 * Includes baseline comparisons, scaling tests, and worst-case scenarios
 */

#include <benchmark/benchmark.h>
#include <sstream>
#include <string>
#include "../../stevensStringLib.h"

// ============================================================================
// BASELINE BENCHMARKS - Compare against standard library
// ============================================================================

static void Separate_Baseline_IStringStream(benchmark::State& state) {
    std::string input = "apple,banana,cherry,date,elderberry,fig,grape,honeydew";

    for (auto _ : state) {
        std::vector<std::string> result;
        std::istringstream ss(input);
        std::string token;
        while(std::getline(ss, token, ',')) {
            result.push_back(token);
        }
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Separate_Baseline_IStringStream);

static void Separate_Baseline_ManualFind(benchmark::State& state) {
    std::string input = "apple,banana,cherry,date,elderberry,fig,grape,honeydew";
    const char sep = ',';

    for (auto _ : state) {
        std::vector<std::string> result;
        size_t start = 0;
        size_t end = input.find(sep);

        while (end != std::string::npos) {
            result.push_back(input.substr(start, end - start));
            start = end + 1;
            end = input.find(sep, start);
        }
        result.push_back(input.substr(start));

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Separate_Baseline_ManualFind);

// ============================================================================
// LIBRARY BENCHMARKS - Char separator
// ============================================================================

static void Separate_Library_Char(benchmark::State& state) {
    std::string input = "apple,banana,cherry,date,elderberry,fig,grape,honeydew";

    for (auto _ : state) {
        auto result = stevensStringLib::separate(input, ',');
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Separate_Library_Char);

// ============================================================================
// LIBRARY BENCHMARKS - String separator
// ============================================================================

static void Separate_Library_String(benchmark::State& state) {
    std::string input = "apple and banana and cherry and date and elderberry";

    for (auto _ : state) {
        auto result = stevensStringLib::separate(input, " and ");
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Separate_Library_String);

// ============================================================================
// SCALING TESTS - How performance changes with input size
// ============================================================================

static void Separate_Scaling(benchmark::State& state) {
    size_t num_elements = state.range(0);

    // Generate input with N elements
    std::string input;
    for(size_t i = 0; i < num_elements; ++i) {
        if(i > 0) input += ",";
        input += "element" + std::to_string(i);
    }

    for (auto _ : state) {
        auto result = stevensStringLib::separate(input, ',');
        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(num_elements);
    state.SetItemsProcessed(state.iterations() * num_elements);
    state.SetBytesProcessed(state.iterations() * input.size());
}
BENCHMARK(Separate_Scaling)
    ->RangeMultiplier(2)
    ->Range(8, 8<<10)
    ->Complexity(benchmark::oN);

// ============================================================================
// WORST CASE - No separators found
// ============================================================================

static void Separate_WorstCase_NoSeparators(benchmark::State& state) {
    size_t str_len = state.range(0);
    std::string input(str_len, 'a');  // Long string with no commas

    for (auto _ : state) {
        auto result = stevensStringLib::separate(input, ',');
        benchmark::DoNotOptimize(result);
    }

    state.SetBytesProcessed(state.iterations() * input.size());
}
BENCHMARK(Separate_WorstCase_NoSeparators)
    ->Range(8, 8<<15);

// ============================================================================
// WORST CASE - Many empty elements
// ============================================================================

static void Separate_WorstCase_ManySeparators(benchmark::State& state) {
    size_t num_seps = state.range(0);
    std::string input(num_seps, ',');  // Just separators: ",,,,,,"

    for (auto _ : state) {
        auto result = stevensStringLib::separate(input, ',', false);  // Don't omit empty
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Separate_WorstCase_ManySeparators)
    ->Range(8, 8<<10);

// ============================================================================
// REAL WORLD - CSV parsing
// ============================================================================

static void Separate_CSV_RealWorld(benchmark::State& state) {
    const std::string csv_line =
        "John,Doe,john.doe@email.com,555-1234,123 Main St,New York,NY,10001";

    for (auto _ : state) {
        auto result = stevensStringLib::separate(csv_line, ',');
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Separate_CSV_RealWorld);

// ============================================================================
// REAL WORLD - Path parsing
// ============================================================================

static void Separate_Path_RealWorld(benchmark::State& state) {
    const std::string path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";

    for (auto _ : state) {
        auto result = stevensStringLib::separate(path, ':');
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Separate_Path_RealWorld);

// ============================================================================
// COMPARISON - Empty separator (split into chars)
// ============================================================================

static void Separate_EmptySeparator(benchmark::State& state) {
    const std::string input = "Hello, World!";

    for (auto _ : state) {
        auto result = stevensStringLib::separate(input, "");
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Separate_EmptySeparator);
