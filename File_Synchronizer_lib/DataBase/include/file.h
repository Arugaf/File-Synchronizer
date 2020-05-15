#ifndef FILE_SYNCHRONIZER_FILE_H
#define FILE_SYNCHRONIZER_FILE_H

#include <filesystem>
#include <string>
#include <utility>

class File {
private:
    std::string filename;
    std::filesystem::path filepath;
public:
    File() = default;
    File(std::string name, std::filesystem::path source): filename(std::move(name)), filepath(std::move(source)) {};
    File(const std::filesystem::path& source) {
        SetFilename(source);
        SetFilepath(source);
    }
    virtual ~File() = default;

    void SetFilename(const std::string& name);
    void SetFilename(const std::filesystem::path& source);
    std::string GetFilename();
    void SetFilepath(const std::filesystem::path& source);
    std::filesystem::path GetFilepath();

    void Print(std::ostream &out);

    bool operator==(const File& right) {
        return this->filepath == right.filepath;
    }
};


#endif //FILE_SYNCHRONIZER_FILE_H
