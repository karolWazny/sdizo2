cmake_minimum_required(VERSION 3.17)
project(structure_templates_lib)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        index.cpp)

set(HEADER_FILES
        structures.h)

add_library(structure_templates_lib ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(array_lib)
add_subdirectory(binary_heap_lib)
add_subdirectory(linked_list_lib)
add_subdirectory(trees_lib)
add_subdirectory(map_lib)

target_link_libraries(structure_templates_lib
        array_lib
        binary_heap_lib
        linked_list_lib
        trees_lib
        map_lib
        )