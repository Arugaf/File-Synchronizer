set(p2p_server p2p_server)

set(p2p_server_path ${PROJECT_SOURCE_DIR}/File_Synchronizer_lib/p2p_server)

set(${p2p_server}_lib_headers_dir ${path}/include)

set(${p2p_server}_lib_sources_dir ${path}/src)
set(${p2p_server}_lib_sources)

add_library(${project_name}_${p2p_server}_lib STATIC ${${p2p_server}_lib_sources})
target_include_directories(${project_name}_${p2p_server}_lib PUBLIC ${${p2p_server}_lib_headers_dir})

add_subdirectory(tests)
enable_testing()