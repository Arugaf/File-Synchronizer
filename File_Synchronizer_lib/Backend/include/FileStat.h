#ifndef FILE_SYNCHRONIZER_FILESTAT_H
#define FILE_SYNCHRONIZER_FILESTAT_H

#include <filesystem>
#include <initializer_list>

namespace FileSynchronizer {
    struct FileStat {
        std::filesystem::file_time_type last_modify_time;
        std::filesystem::file_type file_type = std::filesystem::file_type::regular;
    };
}

#endif //FILE_SYNCHRONIZER_FILESTAT_H
