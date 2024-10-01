add_library(StructsLib AllStructs.cpp )
target_include_directories(StructsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(LibFunc Functions.cpp Parser.cpp ParserLog.cpp )
target_include_directories(LibFunc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})