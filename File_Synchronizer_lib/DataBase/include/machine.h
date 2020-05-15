#ifndef FILE_SYNCHRONIZER_MACHINE_H
#define FILE_SYNCHRONIZER_MACHINE_H

#include <unordered_set>

#include "file.h"

class Machine {
private:
    typedef std::unordered_set<std::filesystem::path, std::hash<std::string>> fileList;

    int id;
    fileList syncFiles;
public:
    Machine() = default;
    Machine(const int& _id): id(_id) {};
    virtual ~Machine() = default;

    void SetId(const int& id_machine);
    int GetId();
    fileList GetSyncFilesListForMachine();
    int GetCountSyncFilesForMachine();
    void AddFileForSync(File file);
    void AddFileForSync(const std::filesystem::path& file);
    void DeleteFileForSync(File file);
    void DeleteFileForSync(const std::filesystem::path& file);
    void ClearSyncFiles();

    void Print(std::ostream &out);

    bool operator==(const Machine& right) {
        return this->id == right.id;
    }
};


#endif //FILE_SYNCHRONIZER_MACHINE_H
