cmake_minimum_required(VERSION 3.17)
project(linked_list_lib)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        LinkedList.h
        LinkedListItem.h
        INextable.h
        )

set(SOURCE_FILES
        index.cpp)

add_library(linked_list_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})