cmake_minimum_required(VERSION 3.17)
project(map_lib)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        TreeMap.h)

set(SOURCE_FILES
        index.cpp)

link_libraries(trees_lib)

add_library(map_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})