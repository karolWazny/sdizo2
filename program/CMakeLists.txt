cmake_minimum_required(VERSION 3.17)
project(sdizo2)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Main.h
        Operations.h
        Randomizer.h
        DirectedOperations.h
        UndirectedOperations.h
        TextFileReader.h
        StopWatch.h)

set(SOURCE_FILES
        Main.cpp
        Operations.cpp
        Randomizer.cpp
        DirectedOperations.cpp
        UndirectedOperations.cpp
        TextFileReader.cpp
        StopWatch.cpp)

link_libraries(graphs)

add_library(program ${SOURCE_FILES} ${HEADER_FILES})