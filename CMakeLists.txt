cmake_minimum_required(VERSION 2.7)   # CMake version check
project(LruCache)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

include_directories(${PROJECT_SOURCE_DIR}/include)
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/test.cc)            # Add main.cpp file of project root directory as source file
add_executable(LruCache ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable
