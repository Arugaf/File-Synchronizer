#ifndef FILE_SYNCHRONIZER_FILE_INFO_FILEMANAGER_H
#define FILE_SYNCHRONIZER_FILE_INFO_FILEMANAGER_H

#include <filesystem>
namespace fs = std::filesystem;

#include "i_filemanager.h"
#include "file.h"
#include "logger.h"

class FileInfoFilemanager : public IFileManager<File> {
private:
    fs::path fileinfo_path;
    ILogger *logger;
public:
    FileInfoFilemanager() : logger(new Logger()) {};
    FileInfoFilemanager(ILogger
    * _logger) {
        logger = _logger;
    };

    void set_fileinfo_path(const fs::path &source);

    fs::path get_fiileinfo_path();

    void Create(const File &file) override;

    void Delete(const File &file) override;

    void Update(const File &file) override;

    File GetFileByFilename(const std::string &filename);
};


#endif //FILE_SYNCHRONIZER_FILE_INFO_FILEMANAGER_H
