# Project
set(tests_name database_tests)

# Sources
set(${database}_tests_sources_dir ${database_path}/tests)
set(${database}_tests_sources ${${database}_tests_sources_dir}/main.cpp
                              ${${database}_tests_sources_dir}/logging_test.cpp
        )


# Executables
add_executable(${tests_name} ${${database}_tests_sources})

target_link_libraries(${tests_name} gtest_main gtest gmock ${${project_name}_${database}_lib})
target_include_directories(${tests_name} PUBLIC ${${database}_lib_headers_dir})

# Tests
add_test(NAME ${tests_name} COMMAND ${tests_name})