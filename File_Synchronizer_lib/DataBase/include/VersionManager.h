#ifndef FILE_SYNCHRONIZER_VERSIONMANAGER_H
#define FILE_SYNCHRONIZER_VERSIONMANAGER_H

#include "VersionCreator.h"
#include "../../include/IVersionManager.h"


class VersionManager : public IVersionManager, public IVersionCreator {
private:
    std::filesystem::path versionsPath;
    std::vector<std::filesystem::path> history;

    VersionCreator* versionCreator;
public:
    VersionManager(const std::filesystem::path& _source): versionCreator(new VersionCreator()) {
        SetVersionsPath(_source);
    }
    VersionManager(const std::filesystem::path& _source, VersionCreator* _versionCreator) {
        SetVersionsPath(_source);
        versionCreator = _versionCreator;
    };
    ~VersionManager() = default;

    void SetVersionsPath(const std::filesystem::path& source);

    // Проиндексировать указанный файл
    void CreateIndex(const std::filesystem::path& file) override;

    // Создать хэш-версию и перезаписать index файла по пути file в соответствующей ему папке в versionsPath
    void CreateVersion(const std::filesystem::path& file) override;

    // Удалить версию version(название файла версии) для file
    int DeleteVersion(const std::filesystem::path& file, const std::string& version) override;

    // Удалить папку с версиями для файла filename
    int DeleteFile(const std::string& filename) override;

    // Вернуть список версий (path to version) для файла по имени filename
    // вернуть все версии (без index) для файла (список отсортирован от самых старых к новым по дате создания)
    // [n] - если запрошенная версия n не существует, то вернет last, иначе i-ю версию по дате
    std::vector<std::filesystem::path> GetVersionHistoryForFile(const std::filesystem::path& filename) override;
    std::vector<std::filesystem::path> GetVersionHistoryForFile(const std::filesystem::path& filename, const int& number) override;
};

#endif //FILE_SYNCHRONIZER_VERSIONMANAGER_H
