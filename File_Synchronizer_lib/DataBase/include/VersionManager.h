#ifndef FILE_SYNCHRONIZER_VERSIONMANAGER_H
#define FILE_SYNCHRONIZER_VERSIONMANAGER_H


#include "TransactionJournal.h"
#include "VersionCreator.h"
#include "iVersionManager.h"


class VersionManager : IVersionManager {
private:
    std::filesystem::path versionsPath;
    std::vector<std::filesystem::path> history;

    VersionCreator* versionCreator;
public:
    VersionManager(): versionCreator(new VersionCreator()) {};
    VersionManager(VersionCreator* _versionCreator) {
        versionCreator = _versionCreator;
    };

    void SetVersionsPath(const std::filesystem::path& source);
    std::filesystem::path GetVersionsPath();

    // Создать хэш-версию и перезаписать index файла по пути file в соответствующей ему папке в versionsPath
    void CreateVersion(const std::filesystem::path& file) override;

    // Удалить версию version(название файла версии) для file
    int DeleteVersion(const std::filesystem::path& file, const std::string& version) override;

    // Удалить папку с версиями для файла filename
    int DeleteFile(const std::string& filename) override;

    // Вернуть список версий (path to version) для файла по имени filename
    // параметры number:
    // * - вернуть все версии (без index) для файла (список отсортирован от самых старых к новым по дате создания)
    // last - вернуть последнюю созданную версию
    // [n] - если запрошенная версия n не существует, то вернет last, иначе i-ю версию по дате
    std::vector<std::filesystem::path> GetVersionHistoryForFile(const std::string& filename, const std::string& number) override;
};

#endif //FILE_SYNCHRONIZER_VERSIONMANAGER_H
