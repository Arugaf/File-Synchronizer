set(backend backend)

# Paths
set(backend_path ${PROJECT_SOURCE_DIR}/File_Synchronizer_lib/Backend)

# Includes
set(${backend}_lib_headers_dir ${path}/include)

# Sources
set(${backend}_lib_sources_dir ${path}/src)
set(${backend}_lib_sources)

# Library
add_library(${project_name}_${backend}_lib STATIC ${${backend}_lib_sources})
target_include_directories(${project_name}_${backend}_lib PUBLIC ${${backend}_lib_headers_dir})

add_subdirectory(tests)
enable_testing()