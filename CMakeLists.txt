cmake_minimum_required(VERSION 3.30.3)
project(AnalyzeLog)

SET(CMAKE_CXX_STANDARD 23)

add_executable(AnalyzeLog bin/main.cpp lib/Functions.cpp lib/Functions.h lib/Parser.cpp lib/Parser.h
lib/ParserLog.cpp lib/ParserLog.h lib/Structs/AllStructs.cpp lib/Structs/AllStructs.h)