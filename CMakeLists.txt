cmake_minimum_required(VERSION 3.30.3)
project(AnalyzeLog)

SET(CMAKE_CXX_STANDARD 23)

add_executable(AnalyzeLog main.cpp Functions.cpp Functions.h Parser.cpp Parser.h WorkCommands.cpp WorkCommands.h)