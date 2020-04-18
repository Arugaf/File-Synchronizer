#ifndef FILE_SYNCHRONIZER_MACHINE_INFO_FILEMANAGER_H
#define FILE_SYNCHRONIZER_MACHINE_INFO_FILEMANAGER_H

#include <filesystem>
namespace fs = std::filesystem;

#include "i_filemanager.h"
#include "machine.h"
#include "logger.h"

class MachineInfoFileManager : public IFileManager<Machine> {
public:
    void Create(const Machine& machine) override;
    void Delete(const Machine& machine) override;
    void Update(const Machine& machine) override;
    Machine GetMachine();
};

#endif //FILE_SYNCHRONIZER_MACHINE_INFO_FILEMANAGER_H
