#include "FileNames.h"

using FileSynchronizer::FileNames;

FileSynchronizer::FileNames::FileNames(FileNames&& other) noexcept {
    file_names = std::move(other.file_names);
}

bool FileNames::Insert(const std::string& file_name) {
    return file_names.insert(file_name).second;
}

bool FileNames::Erase(const std::string& file_name) {
    return static_cast<bool>(file_names.erase(file_name));
}

bool FileNames::Find(const std::string& file_name) const {
    return file_names.find(file_name) != file_names.end();
}

FileNames::FileNames(const std::initializer_list<std::string>& list) : file_names(list) {

}

bool FileSynchronizer::FileNames::IsEmpty() const {
    return file_names.empty();
}

