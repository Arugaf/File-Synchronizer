cmake_minimum_required(VERSION 3.10)
set(Dispatcher_server Dispatcher_server)

# Paths
set(path ${PROJECT_SOURCE_DIR}/)

# Includes
set(${Dispatcher_server}_lib_headers_dir ${path}/include)

# Sources
set(${Dispatcher_server}_lib_sources_dir ${path}/src)
    # Через пробел все файлы
set(${Dispatcher_server}_lib_sources ${${Dispatcher_server}_lib_sources_dir}/class.cpp)

# Library
add_library(${project_name}_${Dispatcher_server}_lib STATIC ${${Dispatcher_server}_lib_sources})
target_include_directories(${project_name}_${Dispatcher_server}_lib PUBLIC ${${Dispatcher_server}_lib_headers_dir})

add_subdirectory(tests)
enable_testing()