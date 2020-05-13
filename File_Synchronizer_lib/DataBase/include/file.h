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
    File(std::string name, std::filesystem::path source): filename(std::move(name)), filepath(std::move(source)) {};
    virtual ~File() = default;

    void SetFilename(const std::string& name);
    std::string GetFilename();
    void SetFilepath(const std::filesystem::path& source);
    std::filesystem::path GetFilepath();

    void Print(std::ostream &out);

    bool operator==(const File& right) {
        return this->filepath == right.filepath;
    }
};


#endif //FILE_SYNCHRONIZER_FILE_H
