cmake_minimum_required(VERSION 3.10)
set(Dispatcher_client Dispatcher_client)

# Paths
set(path ${PROJECT_SOURCE_DIR}/)

# Includes
set(${Dispatcher_client}_lib_headers_dir ${path}/include)

# Sources
set(${Dispatcher_client}_lib_sources_dir ${path}/src)
    # Через пробел все файлы
set(${Dispatcher_client}_lib_sources ${${Dispatcher_client}_lib_sources_dir}/class.cpp)

# Library
add_library(${project_name}_${Dispatcher_client}_lib STATIC ${${Dispatcher_client}_lib_sources})
target_include_directories(${project_name}_${Dispatcher_client}_lib PUBLIC ${${Dispatcher_client}_lib_headers_dir})

add_subdirectory(tests)
enable_testing()