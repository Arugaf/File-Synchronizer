cmake_minimum_required(VERSION 3.10)
# Project
    # Все тесты тут
set(tests_name DispatcherServer)

# Sources
set(${Dispatcher_server}_tests_sources_dir ${path}/tests)
set(${Dispatcher_server}_tests_sources ${${Dispatcher_server}_tests_sources_dir}/main.cpp)
set(gtest_disable_pthreads OFF)

# Executables
add_executable(${tests_name} ${${Dispatcher_server}_tests_sources})

target_link_libraries(${tests_name} gtest_main gtest ${project_name}_${Dispatcher_server}_lib)
target_include_directories(${tests_name} PUBLIC ${${Dispatcher_server}_lib_headers_dir})

# Tests
add_test(NAME ${tests_name} COMMAND ${tests_name})