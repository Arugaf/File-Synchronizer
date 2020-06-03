#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_SRC_FILEMANAGER_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_SRC_FILEMANAGER_H_

#include <chrono>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "IVersionManager.h"
#include "IFileManager.h"
#include "TransactionJournal.h"
#include "VersionManager.h"
#include "FileException.h"

class FileManager : public IFileManager {
private:
    std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> fileList;
    std::vector<std::filesystem::path> deletedFiles;

    std::filesystem::path trackfile;
    std::filesystem::path deletedfile;

    ITransactionJournal<Transaction>* logger;
    VersionManager* versionManager;

    // Перевод времени из file_time_type в читаемое представление
    template <typename TP>
    std::time_t to_time_t(TP tp);

    void LoadTracked();
    void LoadDeleted();
public:
    FileManager(const std::filesystem::path& source): logger(new TransactionJournal(source)), versionManager(new VersionManager(source)) {
        trackfile = source / "syncfilelist.json";
        deletedfile = source / "deletedfilelist.json";
    };

    ~FileManager() override = default;

    // Получить информацию о файле парой (path:time)
    std::pair<std::filesystem::path, std::filesystem::file_time_type> GetFileInfo(const std::filesystem::path& file) override;

    // Полный список пар (path:time)
    // в виде unordered_map, где ключ = path файла
    typedef std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> list;
    list GetInfo() override;

    std::vector<std::filesystem::path> GetDeletedFiles() override;

    // Удалить информацию о файле из списка (из отслеживаемых)
    void DeleteFile(const std::filesystem::path& file) override;

    void RestoreFile(const std::filesystem::path& file) override;
    void RestoreFile(const int &number) override;

    void DeleteFileInstantly(const std::filesystem::path &file) override;

    // Вставляет новый файл, если ключ не найден, или обновляет информацию о существующем
    void SetFileInfo(const std::filesystem::path& file) override;

    // Очистить список отслеживаемых файлов
    void Clear() override;

    int ClearAll() override;

    // Заполнить fileList значениями из trackfile (.json-файл)
    void Load() override;

    // Зафиксировать fileList в trackfile (.json-файл)
    void Save() override;
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_SRC_FILEMANAGER_H_
