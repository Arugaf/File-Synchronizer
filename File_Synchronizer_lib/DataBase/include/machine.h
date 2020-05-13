#ifndef FILE_SYNCHRONIZER_MACHINE_H
#define FILE_SYNCHRONIZER_MACHINE_H

#include <vector>

#include "file.h"

class Machine {
private:
    int id;
    std::vector<File> syncFiles;
public:
    virtual ~Machine() = default;

    void SetId(const int& id_machine);
    int GetId();
    std::vector<File> GetSyncFilesListForMachine();
    int GetCountSyncFilesForMachine();
    void AddFileForSync(const File& file);
    void DeleteFileForSync(const File& file);
    void ClearSyncFiles();

    void Print(std::ostream &out);

    bool operator==(const Machine& right) {
        return this->id == right.id;
    }
};


#endif //FILE_SYNCHRONIZER_MACHINE_H
