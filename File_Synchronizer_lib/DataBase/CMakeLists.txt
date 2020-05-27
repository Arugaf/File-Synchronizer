set(database database)

# Paths
set(database_path ${PROJECT_SOURCE_DIR}/File_Synchronizer_lib/DataBase)

# Includes
set(${database}_lib_headers_dir ${database_path}/include)

# Sources
set(${database}_lib_sources_dir ${database_path}/src)
set(${database}_lib_sources ${${database}_lib_sources_dir}/TransactionJournal.cpp
                            ${${database}_lib_sources_dir}/VersionCreator.cpp
                            ${${database}_lib_sources_dir}/VersionManager.cpp
                            ${${database}_lib_sources_dir}/FileManager.cpp
        )


# BOOSTj
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

# Library
add_library(${project_name}_${database}_lib STATIC ${${database}_lib_sources} ../include/iFileManager.h ../include/iVersionManager.h)
target_include_directories(${project_name}_${database}_lib PUBLIC ${${database}_lib_headers_dir})
target_link_libraries(${project_name}_${database}_lib ${Boost_LIBRARIES})

add_subdirectory(tests)
enable_testing()