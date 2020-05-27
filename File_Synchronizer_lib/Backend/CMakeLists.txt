set(backend backend)

# Paths
set(backend_path ${PROJECT_SOURCE_DIR}/File_Synchronizer_lib/Backend)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -pthread)

# Includes
set(${backend}_lib_headers_dir ${backend_path}/include)

# Sources
set(${backend}_lib_sources_dir ${backend_path}/src)
set(${backend}_lib_sources ${${backend}_lib_sources_dir}/FileWatcher.cpp
                           ${${backend}_lib_sources_dir}/FileNames.cpp
                           ${${backend}_lib_sources_dir}/DataBaseController.cpp
                           ${${backend}_lib_sources_dir}/DataBaseWrapper.cpp
                           ${${backend}_lib_sources_dir}/FileWatcherException.cpp
                           ${${backend}_lib_sources_dir}/ApplicationController.cpp
                           ${${backend}_lib_sources_dir}/VersionManagerWrapper.cpp
                           ${${backend}_lib_sources_dir}/CommandReader.cpp)

# Library
add_library(${project_name}_${backend}_lib STATIC ${${backend}_lib_sources})
target_include_directories(${project_name}_${backend}_lib PUBLIC ${${backend}_lib_headers_dir})
target_link_libraries(${project_name}_${backend}_lib PUBLIC Log_Parser)

add_subdirectory(tests)
enable_testing()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
