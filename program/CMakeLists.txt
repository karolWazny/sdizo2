cmake_minimum_required(VERSION 3.17)
project(sdizo2)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Main.h)

set(SOURCE_FILES
        Main.cpp)

link_libraries(graphs)

add_library(program ${SOURCE_FILES} ${HEADER_FILES})