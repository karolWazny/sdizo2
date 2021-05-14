cmake_minimum_required(VERSION 3.17)
project(sdizo2)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Graph.h
        Path.h
        ListGraph.h
        MatrixGraph.h)

set(SOURCE_FILES
        Path.cpp
        ListGraph.cpp
        MatrixGraph.cpp)

link_libraries(structure_templates_lib)

add_library(graphs ${SOURCE_FILES} ${HEADER_FILES})

