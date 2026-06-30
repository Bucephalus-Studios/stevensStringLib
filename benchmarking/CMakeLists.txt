add_executable(stevensStringLib_benchmarks
    benchmarks/benchmark_separate.cpp
    benchmarks/benchmark_join.cpp
    benchmarks/benchmark_validation.cpp
)

target_link_libraries(stevensStringLib_benchmarks
    PRIVATE
        stevensStringLib
        benchmark::benchmark
)
