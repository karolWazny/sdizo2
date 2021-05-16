cmake_minimum_required(VERSION 3.17)
project(sdizo2)

set(CMAKE_CXX_STANDARD 17)

add_executable(sdizo2 main.cpp)

add_subdirectory(Google_tests)
add_subdirectory(graphs)
add_subdirectory(structure_templates_lib)
add_subdirectory(program)

target_link_libraries(sdizo2 graphs structure_templates_lib program)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()