cmake_minimum_required(VERSION 3.17)
project(sdizo2)

set(CMAKE_CXX_STANDARD 17)

add_executable(sdizo2 main.cpp)

add_subdirectory(Google_tests)
add_subdirectory(graphs)
add_subdirectory(structure_templates_lib)

target_link_libraries(sdizo2 graphs structure_templates_lib)