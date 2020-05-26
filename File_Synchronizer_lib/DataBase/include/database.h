#ifndef FILE_SYNCHRONIZER_DATABASE_H
#define FILE_SYNCHRONIZER_DATABASE_H

#include <filesystem>

template <typename DBImpl>
class DatabaseWrapper {
private:
    std::filesystem::path dbPath;
public:

    ~DatabaseWrapper() = default;

    void SetDbPath(const std::filesystem::path& source) {
        dbPath = source;
    }
    std::filesystem::path GetDbPath() {
        return dbPath;
    }

    void DeleteFile(const std::string& filename) {
        static_cast<DBImpl*>(this)->Delete(filename);
    }
    void CreateFile(const std::string& filename, const std::string& operationTime) {
        static_cast<DBImpl*>(this)->Create(filename, operationTime);
    }
    void UpdateFile(const std::string& filename, const std::string& operationTime) {
        static_cast<DBImpl*>(this)->Update(filename, operationTime);
    }
};


class Database : public DatabaseWrapper<Database> {
private:

public:
    void Delete(const std::string& filename);
    void Create(const std::string& filename, const std::string& operationTime);
    void Update(const std::string& filename, const std::string& operationTime);
};





#endif //FILE_SYNCHRONIZER_DATABASE_H
