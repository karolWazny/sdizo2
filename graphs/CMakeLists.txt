cmake_minimum_required(VERSION 3.17)
project(sdizo2)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Graph.h
        Path.h)

set(SOURCE_FILES
        Graph.cpp
        Path.cpp)

add_library(graphs ${SOURCE_FILES} ${HEADER_FILES})
