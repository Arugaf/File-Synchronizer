set(tests_name)

set(${p2p_client}_tests_sources_dir ${path}/tests)
set(${p2p_client}_tests_sources ${${p2p_client}_tests_sources_dir}/main.cpp)

add_executable(${tests_name} ${${p2p_client}_tests_sources})

target_link_libraries(${tests_name} gtest_main gtest ${project_name}_${p2p_client}_lib)
target_include_directories(${tests_name} PUBLIC ${${p2p_client}_lib_headers_dir})

add_test(NAME ${tests_name} COMMAND ${tests_name})