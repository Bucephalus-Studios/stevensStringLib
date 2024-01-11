cmake_minimum_required(VERSION 3.22.1)

project(benchmarkStevensStringLib C CXX)

add_executable(${PROJECT_NAME} benchmark.cpp)

# GoogleTest requires at least C++14, and stevensStringLib takes C++23
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googlebenchmark)


#add_library(${PROJECT_NAME} STATIC ${Sources}) #${Headers})

target_link_libraries(${PROJECT_NAME} PUBLIC
	benchmark::benchmark
)
