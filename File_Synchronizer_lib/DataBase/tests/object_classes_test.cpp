#include <gtest/gtest.h>

#include "user.h"
#include "file.h"
#include "machine.h"

TEST(UserTest, SetUsername) {
    User testUser;

    testUser.SetUsername("Example");

    EXPECT_EQ(testUser.GetUsername(), "Example");
}

TEST(UserTest, MachineAddOperations) {
    User testUser("exampleUser");

    Machine first(1);
    Machine second(2);

    testUser.AddConnectedMachine(first);
    EXPECT_EQ(testUser.GetCountConnectedMachines(), 1);
    testUser.AddConnectedMachine(first);
    EXPECT_EQ(testUser.GetCountConnectedMachines(), 1);

    testUser.AddConnectedMachine(second.GetId());
    EXPECT_EQ(testUser.GetCountConnectedMachines(), 2);
}

TEST(UserTest, MachineDeleteOperations) {
    User testUser("exampleUser");

    Machine first(1);
    Machine second(2);

    testUser.AddConnectedMachine(first);
    testUser.AddConnectedMachine(second);

    testUser.DeleteConnectedMachine(first);
    EXPECT_EQ(testUser.GetCountConnectedMachines(), 1);

    testUser.DeleteConnectedMachine(second.GetId());
    EXPECT_EQ(testUser.GetCountConnectedMachines(), 0);
}

TEST(FileTest, SetFileParameters) {
    File file;

    std::string name = "test.txt";
    std::filesystem::path path = "" + name;

    file.SetFilename(name);
    file.SetFilepath(path);
    EXPECT_EQ(file.GetFilename(), name);
    EXPECT_EQ(file.GetFilepath(), path);
}

TEST(MachineTest, SetId) {
    Machine machine;
    int idTest = 100500;

    machine.SetId(idTest);

    EXPECT_EQ(machine.GetId(), idTest);
}

TEST(MachineTest, FileAddOperations) {
    Machine machine(100500);

    std::string name = "test.txt";
    std::filesystem::path path = "" + name;
    File file(name, path);

    std::filesystem::path anotherPath = "somedir/" + name;

    machine.AddFileForSync(file);
    EXPECT_EQ(machine.GetCountSyncFilesForMachine(), 1);
    machine.AddFileForSync(file);
    EXPECT_EQ(machine.GetCountSyncFilesForMachine(), 1);

    machine.AddFileForSync(anotherPath);
    EXPECT_EQ(machine.GetCountSyncFilesForMachine(), 2);
}

TEST(MachineTest, FileDeleteOperations) {
    Machine machine(100500);

    std::string name = "test.txt";
    std::filesystem::path path = "" + name;
    File file(name, path);
    machine.AddFileForSync(path);

    for (int i = 0; i < 5; i++) {
        name = "test" + std::to_string(i) + ".txt";
        path = "somedir/" + name;

        machine.AddFileForSync(path);
    }

    EXPECT_EQ(machine.GetCountSyncFilesForMachine(), 6);

    machine.DeleteFileForSync(file);
    EXPECT_EQ(machine.GetCountSyncFilesForMachine(), 5);

    std::filesystem::path existing = "somedir/test0.txt";
    std::filesystem::path nonexisting = "example.txt";

    machine.DeleteFileForSync(existing);
    EXPECT_EQ(machine.GetCountSyncFilesForMachine(), 4);

    machine.DeleteFileForSync(nonexisting);
    EXPECT_EQ(machine.GetCountSyncFilesForMachine(), 4);

    machine.ClearSyncFiles();
    EXPECT_EQ(machine.GetCountSyncFilesForMachine(), 0);
}