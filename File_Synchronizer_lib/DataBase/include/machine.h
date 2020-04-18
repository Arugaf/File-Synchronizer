#ifndef FILE_SYNCHRONIZER_MACHINE_H
#define FILE_SYNCHRONIZER_MACHINE_H

#include <vector>

#include "file.h"

class Machine {
private:
    int id;
    std::vector<File> sync_files;
public:
    void set_id(const int& id_machine);
    int get_id();
    std::vector<File> GetSyncFilesListForMachine();
    int GetCountSyncFilesForMachine();
    void AddFileForSync(const File& file);
    void DeleteFileForSync(const File& file);
    void ClearSyncFiles();
};


#endif //FILE_SYNCHRONIZER_MACHINE_H
