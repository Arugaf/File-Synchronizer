#ifndef FILE_SYNCHRONIZER_FILEMANAGERS_H
#define FILE_SYNCHRONIZER_FILEMANAGERS_H

#include <fstream>
#include <utility>

#include "transactionjournal.h"
#include "machine.h"
#include "user.h"
#include "file.h"

// -------------------------------------- BASE --------------------------------------
template <typename T>
class IFileManager {
private:
    void PrintInFile(T object, const std::filesystem::path& sourcefile) {
        std::ofstream file(sourcefile);
        if (file.is_open()) {
            object.Print(file);
        }
        file.close();
    }
public:
    virtual ~IFileManager() = default;

    virtual void Create(T object, const std::filesystem::path& source) {
        try {
            std::filesystem::create_directories(source);

            PrintInFile(object, source);

        } catch (std::filesystem::filesystem_error& exception) {
            throw exception;
        }
    };

    virtual void Delete(T object, const std::filesystem::path& source) {
        int success = 0;
        try {
            success = std::filesystem::remove_all(source);

        } catch (std::filesystem::filesystem_error& exception) {
            throw success;
        }
    };

    virtual void Update(T object, const std::filesystem::path& source) {
        try {
            PrintInFile(object, source);

        } catch (std::filesystem::filesystem_error& exception) {
            throw exception;
        }
    };
};
// ----------------------------------------------------------------------------------



// -------------------------------------- USER --------------------------------------
class UserInfoFileManager : public IFileManager<User> {
private:
    std::filesystem::path usersPath;
    ITransactionJournal* logger;
public:
    UserInfoFileManager(): logger(new TransactionJournal()) {};
    explicit UserInfoFileManager(ITransactionJournal* _logger) {
        logger = _logger;
    };
    ~UserInfoFileManager() override = default;

    void SetUsersPath(const std::filesystem::path& source);
    std::filesystem::path GetUsersPath();

    void Create(User user);
    void Delete(User user);
    void Update(User user);
    User GetUserByUsername(const std::string& username);
};

void UserInfoFileManager::SetUsersPath(const std::filesystem::path &source) {
    usersPath = source;
}

std::filesystem::path UserInfoFileManager::GetUsersPath() {
    return usersPath;
}

void UserInfoFileManager::Create(User user)  {
    std::string path = user.GetUsername() + "/" + user.GetUsername() + ".txt";
    try {
        IFileManager::Create(user, path);

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl
            << "If you trying to edit info about existing user, try Update function";
    }

    Transaction transaction(Operation::created, usersPath / path, 1);
    transaction.FormMessage();
    logger->AddTransaction(transaction);
}

void UserInfoFileManager::Delete(User user) {
    try {
        IFileManager::Delete(user, usersPath / user.GetUsername());

    } catch (const int& count) {
        std::ostringstream msg;
        msg << "Deleted" << count << "files and directories (should be 2)" << std::endl;
    }

    Transaction transaction(Operation::deleted, usersPath / user.GetUsername(), 1);
    transaction.FormMessage();
    logger->AddTransaction(transaction);
}

void UserInfoFileManager::Update(User user) {
    std::string path = user.GetUsername() + "/" + user.GetUsername() + ".txt";
    try {
        IFileManager::Update(user, path);

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl
            << "If you trying to create new user, try Create function";
    }

    Transaction transaction(Operation::edited, usersPath / path, 1);
    transaction.FormMessage();
    logger->AddTransaction(transaction);
}

User UserInfoFileManager::GetUserByUsername(const std::string &username) {
    std::string path = username + "/" + username + ".txt";
    User user;

    try {
        std::ifstream file(usersPath / path);
        if (file.is_open()) {
            std::string name;
            std::string machine;

            std::getline(file, name);
            user.SetUsername(name);

            while (std::getline(file, machine, ' ')) {
                user.AddConnectedMachine(std::stoi(machine));
            }
        }
        file.close();

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl;
    }

    return user;
}
// ----------------------------------------------------------------------------------



// ------------------------------------ MACHINE -------------------------------------
class MachineInfoFileManager : public IFileManager<Machine> {
private:
    std::filesystem::path machineinfoPath;
public:
    explicit MachineInfoFileManager(const std::filesystem::path& source): {
        SetMachineinfoPath(source);
    };
    ~MachineInfoFileManager() override = default;

    void SetMachineinfoPath(const std::filesystem::path &source);
    std::filesystem::path GetMachineinfoPath();

    void Create(const Machine& machine);
    void Delete(const Machine& machine);
    void Update(Machine machine);
    Machine GetMachine();
};

void MachineInfoFileManager::SetMachineinfoPath(const std::filesystem::path &source) {
    machineinfoPath = source / "machineinfo.txt";
    std::filesystem::create_directories(machineinfoPath);
}

std::filesystem::path MachineInfoFileManager::GetMachineinfoPath() {
    return machineinfoPath;
}

void MachineInfoFileManager::Create(const Machine& machine) {
    try {
        IFileManager::Create(machine, machineinfoPath);

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl;
    }
}

void MachineInfoFileManager::Delete(const Machine& machine) {
    try {
        IFileManager::Delete(machine, machineinfoPath);

    } catch (const int& count) {
        std::ostringstream msg;
        msg << "Deleted" << count << "files and directories (should be 1)" << std::endl;
    }
}

void MachineInfoFileManager::Update(Machine machine) {
    try {
        IFileManager::Update(machine, machineinfoPath);

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl;
    }
}

Machine MachineInfoFileManager::GetMachine() {


    return Machine();
}
// ----------------------------------------------------------------------------------
// TODO: class filesystem в machinetest + struct directory (name) + struct file (name content)


// ------------------------------------- FILE ---------------------------------------
class FileInfoFilemanager : public IFileManager<File> {
private:
    std::filesystem::path fileinfoPath;
    ITransactionJournal *logger;
public:
    FileInfoFilemanager() : logger(new TransactionJournal()) {};
    explicit FileInfoFilemanager(ITransactionJournal * _logger) {
        logger = _logger;
    };
    ~FileInfoFilemanager() override = default;

    void SetFileinfoPath(const std::filesystem::path &source);
    std::filesystem::path GetFileinfoPath();

    void Create(File file);
    void Delete(File file);
    void Update(File file);
    File GetFileByFilename(const std::string &filename);
};

void FileInfoFilemanager::SetFileinfoPath(const std::filesystem::path &source) {
    fileinfoPath = source;
}

std::filesystem::path FileInfoFilemanager::GetFileinfoPath() {
    return fileinfoPath;
}

void FileInfoFilemanager::Create(File file) {
    std::string path = file.GetFilename() + ".txt";
    try {
        IFileManager::Create(file, fileinfoPath / path);

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl
            << "If you trying to edit info about existing file, try Update function";
    }

    Transaction transaction(Operation::created, fileinfoPath / path, 1);
    transaction.FormMessage();
    logger->AddTransaction(transaction);
}

void FileInfoFilemanager::Delete(File file) {
    try {
        IFileManager::Delete(file, fileinfoPath / file.GetFilename());

    } catch (const int& count) {
        std::ostringstream msg;
        msg << "Deleted" << count << "files and directories (should be 2)" << std::endl;
    }

    Transaction transaction(Operation::deleted, fileinfoPath / file.GetFilename(), 1);
    transaction.FormMessage();
    logger->AddTransaction(transaction);
}

void FileInfoFilemanager::Update(File file) {
    try {
        IFileManager::Update(file, fileinfoPath / file.GetFilename());

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl;
    }

    Transaction transaction(Operation::edited, fileinfoPath / file.GetFilename(), 1);
    transaction.FormMessage();
    logger->AddTransaction(transaction);
}

File FileInfoFilemanager::GetFileByFilename(const std::string &filename) {
    std::string path = filename + ".txt";
    std::string name;
    std::string source;
    std::string blacklist;

    try {
        std::ifstream fileinfo(fileinfoPath / path);
        if (fileinfo.is_open()) {
            std::getline(fileinfo, name);
            std::getline(fileinfo, source);
            std::getline(fileinfo, blacklist);

        }
        fileinfo.close();

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl;
    }

    File file(name, source);
    if (std::stoi(blacklist)) {
        file.AddFileToBlacklist();
    }

    return file;
}

// ----------------------------------------------------------------------------------

#endif //FILE_SYNCHRONIZER_FILEMANAGERS_H