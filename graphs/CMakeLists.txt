cmake_minimum_required(VERSION 3.17)
project(sdizo2)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Graph.h
        Path.h
        ListGraph.h
        MatrixGraph.h
        GraphGenerator.h
        GraphFactory.h
        ListGraphFactory.h
        MatrixGraphFactory.h)

set(SOURCE_FILES
        Path.cpp
        ListGraph.cpp
        MatrixGraph.cpp
        Graph.cpp
        GraphGenerator.cpp
        ListGraphFactory.cpp
        MatrixGraphFactory.cpp)

link_libraries(structure_templates_lib)

add_library(graphs ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

