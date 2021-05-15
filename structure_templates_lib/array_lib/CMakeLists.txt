cmake_minimum_required(VERSION 3.17)
project(array_lib)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Array.h
        ArrayIterator.h)

set(SOURCE_FILES
        index.cpp)

add_library(array_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})