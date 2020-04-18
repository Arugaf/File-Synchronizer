set(database database)

# Paths
set(database_path ${PROJECT_SOURCE_DIR}/File_Synchronizer_lib/DataBase)

# Includes
set(${database}_lib_headers_dir ${database_path}/include)

# Sources
set(${database}_lib_sources_dir ${database_path}/src)
set(${database}_lib_sources ${${database}_lib_sources_dir}/file.cpp
                            ${${database}_lib_sources_dir}/logger.cpp
                            ${${database}_lib_sources_dir}/machine.cpp
                            ${${database}_lib_sources_dir}/transaction.cpp
                            ${${database}_lib_sources_dir}/transactionjournal.cpp
                            ${${database}_lib_sources_dir}/user.cpp
                            ${${database}_lib_sources_dir}/version.cpp
                            ${${database}_lib_sources_dir}/versioncreator.cpp
                            ${${database}_lib_sources_dir}/versionmanager.cpp
                            ${${database}_lib_sources_dir}/user_info_filemanager.cpp
                            ${${database}_lib_sources_dir}/machine_info_filemanager.cpp
                            ${${database}_lib_sources_dir}/file_info_filemanager.cpp
                            ${${database}_lib_sources_dir}/database.cpp
        )


# Library
add_library(${project_name}_${database}_lib STATIC ${${database}_lib_sources})
target_include_directories(${project_name}_${database}_lib PUBLIC ${${database}_lib_headers_dir})

add_subdirectory(tests)
enable_testing()