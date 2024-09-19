cmake_minimum_required(VERSION 3.30.3)
project(labwork1 VERSION 0.1.0 LANGUAGES C CXX)

SET(CMAKE_CXX_STANDARD 23)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(AnalyzeLog main.cpp)

