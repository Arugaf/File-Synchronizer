set(backend backend)

# Paths
set(backend_path ${PROJECT_SOURCE_DIR}/File_Synchronizer_lib/Backend)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -pthread)

# Includes
set(${backend}_lib_headers_dir ${backend_path}/include)

# Sources
set(${backend}_lib_sources_dir ${backend_path}/src)
set(${backend}_lib_sources ${${backend}_lib_sources_dir}/FileWatcher.cpp
                           ${${backend}_lib_sources_dir}/SyncController.cpp)

# Library
add_library(${project_name}_${backend}_lib STATIC ${${backend}_lib_sources})
target_include_directories(${project_name}_${backend}_lib PUBLIC ${${backend}_lib_headers_dir})

add_executable(test_exec ../../main.cpp)
target_link_libraries(test_exec PUBLIC ${project_name}_${backend}_lib)

add_subdirectory(tests)
enable_testing()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
