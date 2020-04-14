cmake_minimum_required(VERSION 3.15)

set(project_name File_Synchronizer)
project(${project_name})

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

add_subdirectory(googletest)
add_subdirectory(${project_name}_lib)