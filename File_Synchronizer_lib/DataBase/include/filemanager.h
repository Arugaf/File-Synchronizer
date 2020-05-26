#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_SRC_FILEMANAGER_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_SRC_FILEMANAGER_H_

#include <filesystem>
#include <unordered_map>
#include <utility>

class FileManager {
private:
    std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> fileList;
    std::filesystem::path trackfile;

    template <typename TP>
    std::time_t to_time_t(TP tp) {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                                + system_clock::now());
        return system_clock::to_time_t(sctp);
    }

public:
    FileManager(std::filesystem::path source): trackfile(std::move(source)) {};

    // Получить информацию о файле парой (path:time)
    std::pair<std::filesystem::path, std::filesystem::file_time_type> GetFileInfo(const std::filesystem::path& file);

    // Полный список пар (path:time)
    // в виде unordered_map, где ключ = path файла
    typedef std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> list;
    list GetInfo();

    // Удалить информацию о файле из списка (из отслеживаемых)
    void DeleteFile(const std::filesystem::path& file);

    // Вставляет новый файл, если ключ не найден, или обновляет информацию о существующем
    void SetFileInfo(const std::filesystem::path& file);

    // Очистить список отслеживаемых файлов
    void Clear();

    // Заполнить fileList значениями из trackfile (.json-файл)
    void Load();

    // Зафиксировать fileList в trackfile (.json-файл)
    void Save();
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_SRC_FILEMANAGER_H_
