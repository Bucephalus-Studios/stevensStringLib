cmake_minimum_required(VERSION 3.16)
project(stevensStringLib LANGUAGES CXX)

add_library(stevensStringLib INTERFACE)
add_library(stevensStringLib::stevensStringLib ALIAS stevensStringLib)

target_include_directories(stevensStringLib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(stevensStringLib INTERFACE cxx_std_17)
