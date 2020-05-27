#ifndef FILE_SYNCHRONIZER_FILEWATCHER_HPP
#define FILE_SYNCHRONIZER_FILEWATCHER_HPP

template<typename T>
inline bool FileSynchronizer::FileWatcher::IsExisting(const T& file) const {
    return std::filesystem::exists(file->first);
}

template<typename T>
inline bool FileSynchronizer::FileWatcher::IsRegular(const T& file) const {
    return file->second.file_type == std::filesystem::file_type::regular;
}

template<typename T>
inline bool FileSynchronizer::FileWatcher::IsChanged(const T& file) const {
    return std::filesystem::last_write_time(file->first) != file->second.last_modify_time;
}

template<typename T>
void FileSynchronizer::FileWatcher::UpdateFile(T&& file, FileSynchronizer::FileStatus status) {
    if (IsRegular(file)) {
        changed_files[std::filesystem::path(file->first)] = status;
    }

    switch (status) {
        case (FileStatus::Modified): {
            file->second.last_modify_time = std::filesystem::last_write_time(file->first);
            break;
        }

        case (FileStatus::Deleted): {
            file = files.erase(file);
            break;
        }

        default: {
            break;
        }
    }
}

#endif //FILE_SYNCHRONIZER_FILEWATCHER_HPP
