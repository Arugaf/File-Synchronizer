# Project
    # Все тесты тут
set(tests_name DispatcherClient)

# Sources
set(${Dispatcher_client}_tests_sources_dir ${path}/tests)
set(${Dispatcher_client}_tests_sources ${${Dispatcher_client}_tests_sources_dir}/main.cpp)

# Executables
add_executable(${tests_name} ${${Dispatcher_client}_tests_sources})

target_link_libraries(${tests_name} gtest_main gtest ${project_name}_${Dispatcher_client}_lib)
target_include_directories(${tests_name} PUBLIC ${${Dispatcher_client}_lib_headers_dir})

# Tests
add_test(NAME ${tests_name} COMMAND ${tests_name})