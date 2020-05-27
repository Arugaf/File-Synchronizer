find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_library(Log_Parser STATIC src/LogParser.cpp)
target_include_directories(Log_Parser PUBLIC include)