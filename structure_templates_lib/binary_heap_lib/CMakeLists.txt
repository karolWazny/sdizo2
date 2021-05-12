cmake_minimum_required(VERSION 3.17)
project(binary_heap_lib)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        BinaryHeap.h
        FixedMinimumHeap.h)

set(SOURCE_FILES
        index.cpp)

add_library(binary_heap_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})