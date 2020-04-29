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
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(Boost 1.65.1 REQUIRED system)
find_package (Threads REQUIRED)
SET(Boost_USE_MULTITHREADED ON)
FIND_LIBRARY(SQLITE3_LIBRARY NAMES sqlite3)

set(gtest_disable_pthreads OFF)

# Library
add_library(${project_name}_${Dispatcher_server}_lib STATIC ${${Dispatcher_server}_lib_sources})
target_include_directories(${project_name}_${Dispatcher_server}_lib PUBLIC ${${Dispatcher_server}_lib_headers_dir} /usr/include)
target_link_libraries(${project_name}_${Dispatcher_server}_lib PUBLIC ${Boost_LIBRARIES} -lpthread -lm sqlite3)
link_directories(/usr/lib)

add_subdirectory(tests)
enable_testing()