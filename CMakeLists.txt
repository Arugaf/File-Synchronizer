cmake_minimum_required(VERSION 3.15)

set(project_name File_Synchronizer)
project(${project_name})
set(backend_path ${PROJECT_SOURCE_DIR})
set(database_path ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

add_subdirectory(googletest)
add_subdirectory(${project_name}_lib)

add_executable(app main.cpp)
message(File_Synchronizer_backend_lib)
target_link_libraries(app PUBLIC File_Synchronizer_backend_lib File_Synchronizer_database_lib pthread)
target_include_directories(app PUBLIC ${backend}_lib_headers_dir)
