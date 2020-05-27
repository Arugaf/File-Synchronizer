#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_SRC_FILEMANAGER_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_SRC_FILEMANAGER_H_

#include "iVersionManager.h"
#include "iFileManager.h"
#include "TransactionJournal.h"
#include "VersionManager.h"

class FileManager : public IFileManager {
private:
    std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> fileList;
    std::filesystem::path trackfile;

    ITransactionJournal<Transaction>* logger;
    VersionManager* versionManager;

    // Перевод времени из file_time_type в читаемое человеком представление
    template <typename TP>
    std::time_t to_time_t(TP tp);

public:
    FileManager(const std::filesystem::path& source): logger(new TransactionJournal(source)), versionManager(new VersionManager(source)) {
        trackfile = source / "syncfilelist.json";
    };

    ~FileManager() override = default;

    // Получить информацию о файле парой (path:time)
    std::pair<std::filesystem::path, std::filesystem::file_time_type> GetFileInfo(const std::filesystem::path& file) override;

    // Полный список пар (path:time)
    // в виде unordered_map, где ключ = path файла
    typedef std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> list;
    list GetInfo() override;

    // Удалить информацию о файле из списка (из отслеживаемых)
    void DeleteFile(const std::filesystem::path& file) override;

    // Вставляет новый файл, если ключ не найден, или обновляет информацию о существующем
    void SetFileInfo(const std::filesystem::path& file) override;

    // Очистить список отслеживаемых файлов
    void Clear() override;

    // Заполнить fileList значениями из trackfile (.json-файл)
    void Load() override;

    // Зафиксировать fileList в trackfile (.json-файл)
    void Save() override;
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_SRC_FILEMANAGER_H_
