/**
 * @file benchmark_join.cpp
 * @brief Comprehensive benchmarks for join() function
 */

#include <benchmark/benchmark.h>
#include <numeric>
#include "../../stevensStringLib.h"

// ============================================================================
// BASELINE BENCHMARKS
// ============================================================================

static void BM_Join_Baseline_Accumulate(benchmark::State& state) {
    std::vector<std::string> vec = {"apple", "banana", "cherry", "date", "elderberry"};
    std::string separator = ", ";

    for (auto _ : state) {
        std::string result;
        for(size_t i = 0; i < vec.size(); ++i) {
            if(i > 0) result += separator;
            result += vec[i];
        }
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Join_Baseline_Accumulate);

// ============================================================================
// LIBRARY BENCHMARKS
// ============================================================================

static void BM_Join_Library_Small(benchmark::State& state) {
    std::vector<std::string> vec = {"apple", "banana", "cherry", "date", "elderberry"};
    std::string separator = ", ";

    for (auto _ : state) {
        auto result = stevensStringLib::join(vec, separator);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Join_Library_Small);

// ============================================================================
// SCALING TESTS
// ============================================================================

static void BM_Join_Scaling(benchmark::State& state) {
    size_t num_elements = state.range(0);

    // Generate vector with N elements
    std::vector<std::string> vec;
    vec.reserve(num_elements);
    for(size_t i = 0; i < num_elements; ++i) {
        vec.push_back("element" + std::to_string(i));
    }

    for (auto _ : state) {
        auto result = stevensStringLib::join(vec, ",");
        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(num_elements);
    state.SetItemsProcessed(state.iterations() * num_elements);
}
BENCHMARK(BM_Join_Scaling)
    ->RangeMultiplier(2)
    ->Range(8, 8<<10)
    ->Complexity(benchmark::oN);

// ============================================================================
// WORST CASE - Many empty strings
// ============================================================================

static void BM_Join_WorstCase_EmptyStrings(benchmark::State& state) {
    size_t num_elements = state.range(0);
    std::vector<std::string> vec(num_elements, "");  // All empty

    for (auto _ : state) {
        auto result = stevensStringLib::join(vec, ",");
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Join_WorstCase_EmptyStrings)
    ->Range(8, 8<<10);

// ============================================================================
// SEPARATOR LENGTH IMPACT
// ============================================================================

static void BM_Join_LongSeparator(benchmark::State& state) {
    std::vector<std::string> vec = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    std::string long_sep = " --- separator --- ";

    for (auto _ : state) {
        auto result = stevensStringLib::join(vec, long_sep);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Join_LongSeparator);

static void BM_Join_ShortSeparator(benchmark::State& state) {
    std::vector<std::string> vec = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

    for (auto _ : state) {
        auto result = stevensStringLib::join(vec, ",");
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Join_ShortSeparator);

// ============================================================================
// REAL WORLD - CSV generation
// ============================================================================

static void BM_Join_CSV_RealWorld(benchmark::State& state) {
    std::vector<std::string> record = {
        "John", "Doe", "john.doe@email.com", "555-1234",
        "123 Main St", "New York", "NY", "10001"
    };

    for (auto _ : state) {
        auto result = stevensStringLib::join(record, ",");
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Join_CSV_RealWorld);

// ============================================================================
// ROUNDTRIP - separate then join
// ============================================================================

static void BM_Join_Roundtrip(benchmark::State& state) {
    std::string original = "apple,banana,cherry,date,elderberry,fig,grape";

    for (auto _ : state) {
        auto separated = stevensStringLib::separate(original, ',');
        auto rejoined = stevensStringLib::join(separated, ",");
        benchmark::DoNotOptimize(rejoined);
    }
}
BENCHMARK(BM_Join_Roundtrip);
