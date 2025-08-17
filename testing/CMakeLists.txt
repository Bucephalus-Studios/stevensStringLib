cmake_minimum_required(VERSION 3.22.1)

project(testStevensStringLib C CXX)

add_executable(${PROJECT_NAME} test.cpp)

# GoogleTest requires at least C++14, and stevensStringLib requires C++17
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

#add_library(${PROJECT_NAME} STATIC ${Sources}) #${Headers})

target_link_libraries(${PROJECT_NAME} PUBLIC
	gtest_main
)

add_test(
	NAME ${PROJECT_NAME}
	COMMAND ${PROJECT_NAME}
)
