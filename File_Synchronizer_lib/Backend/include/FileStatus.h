#ifndef FILE_SYNCHRONIZER_FILESTATUS_H
#define FILE_SYNCHRONIZER_FILESTATUS_H

namespace FileSynchronizer {
    enum class FileStatus {
        Modified,
        Created,
        Deleted
    };
}

#endif //FILE_SYNCHRONIZER_FILESTATUS_H
