cmake_minimum_required(VERSION 3.15)
project(Backprop)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

file(GLOB_RECURSE SOURCE src/*.cpp src/*.hpp src/*.h)

set(CMAKE_CXX_STANDARD 17)
add_executable(Backprop ${SOURCE} main.cpp)