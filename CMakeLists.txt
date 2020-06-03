cmake_minimum_required(VERSION 3.15)

set(project_name File_Synchronizer)
project(${project_name})
set(backend_path ${PROJECT_SOURCE_DIR})
set(database_path ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
#set(CMAKE_CXX_FLAGS "-lboost_program_options")

add_subdirectory(googletest)
add_subdirectory(${project_name}_lib)

add_executable(Watcher main.cpp)
#message(File_Synchronizer_backend_lib)
target_link_libraries(Watcher PUBLIC File_Synchronizer_backend_lib File_Synchronizer_database_lib pthread)
target_include_directories(Watcher PUBLIC ${backend}_lib_headers_dir)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Overwatch commands.cpp)
target_link_libraries(Overwatch PUBLIC File_Synchronizer_backend_lib File_Synchronizer_database_lib pthread boost_program_options)
target_include_directories(Overwatch PUBLIC ${backend}_lib_headers_dir)