#ifndef FILE_SYNCHRONIZER_FILENAMES_H
#define FILE_SYNCHRONIZER_FILENAMES_H

#include <initializer_list>
#include <unordered_set>

namespace FileSynchronizer {
    class FileNames {
    public:
        FileNames() = default;
        FileNames(const std::initializer_list<std::string>& list);

        FileNames(FileNames&& other) noexcept;

        ~FileNames() = default;

        bool Insert(const std::string& file_name);
        bool Erase(const std::string& file_name);
        bool Find(const std::string& file_name) const;
        bool IsEmpty() const;

    private:
        std::unordered_set<std::string> file_names;
    };
}

#endif //FILE_SYNCHRONIZER_FILENAMES_H
