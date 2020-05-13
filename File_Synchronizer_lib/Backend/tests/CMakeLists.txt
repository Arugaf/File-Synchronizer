# Project
set(tests_name backend_tests)

# Sources
set(${backend}_tests_sources_dir ${backend_path}/tests)
set(${backend}_tests_sources ${${backend}_tests_sources_dir}/main.cpp
                             ${${backend}_tests_sources_dir}/FileWatcherTests.cpp)

# Executables
add_executable(${tests_name} ${${backend}_tests_sources})

target_link_libraries(${tests_name} gtest_main gtest gmock ${project_name}_${backend}_lib)
target_include_directories(${tests_name} PUBLIC ${${backend}_lib_headers_dir})

# Tests
add_test(NAME ${tests_name} COMMAND ${tests_name})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")

