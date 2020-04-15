#include <gtest/gtest.h>

#include "machine.h"

TEST(SetParam, SetMachineID){
    Machine m;
    int machine_id = 100500;

    m.set_machine_id(machine_id);
    EXPECT_EQ(m.get_machine_id(), machine_id);
}

TEST(SetParam, SetMachineDBPath){
    Machine m(1);
    std::filesystem::path source = "/etc/db/";

    m.set_db_path(source);
    EXPECT_EQ(m.get_db_path(), source);
}

// -------------------------------------------------------------------
class MachineFixture {
public:
    Machine machine;
    bool userdir_status = false;
    bool versiondir_status = false;
    bool journaldir_status = false;
};

class MachineFixtureTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::filesystem::path source = "/etc/db/";
        mtest.machine.set_machine_id(1);
        mtest.machine.set_db_path(source);

        mtest.machine.CreateDBDirectories();

        mtest.userdir_status = std::filesystem::exists("/etc/db/users/");
        mtest.versiondir_status = std::filesystem::exists("/etc/db/versions/");
        mtest.journaldir_status = std::filesystem::exists("/etc/db/trjournal/");
    }
    void TearDown() override {}

    MachineFixture mtest;
};

TEST_F(MachineFixtureTest, CreateDBDirectories) {
    EXPECT_TRUE(mtest.userdir_status);
    EXPECT_TRUE(mtest.versiondir_status);
    EXPECT_TRUE(mtest.journaldir_status);
}

TEST_F(MachineFixtureTest, CreateExistingDBDirectories) {
    if (mtest.userdir_status && mtest.versiondir_status && mtest.journaldir_status) {
        EXPECT_TRUE(mtest.machine.CreateDBDirectories());
    }
}

TEST_F(MachineFixtureTest, DeleteExistingDirectories) {
    if (mtest.userdir_status && mtest.versiondir_status && mtest.journaldir_status) {
        EXPECT_FALSE(mtest.machine.DeleteDBDirectories());
    }
}

TEST_F(MachineFixtureTest, DeleteNonexistingDirectories) {
    mtest.machine.DeleteDBDirectories();
    EXPECT_TRUE(mtest.machine.DeleteDBDirectories());
}

TEST_F(MachineFixtureTest, CreateFileDirectory){
    std::string filename = "file1.txt";

    mtest.machine.CreateDirectoryForFile(filename);

    auto status = std::filesystem::exists("/etc/db/versions/file1/");
    EXPECT_TRUE(status);
}

TEST_F(MachineFixtureTest, CreateExistingFileDirectory) {
    std::string filename = "file1.txt";

    mtest.machine.CreateDirectoryForFile(filename);

    auto status = std::filesystem::exists("/etc/db/versions/file1/");
    if (status) {
        EXPECT_TRUE(mtest.machine.CreateDirectoryForFile(filename));
    }

}

TEST_F(MachineFixtureTest, DeleteNonexistingFileDirectory){
    std::string filename = "file1.txt";

    auto status = std::filesystem::exists("/etc/db/versions/file1/");
    if (!status) {
        EXPECT_TRUE(mtest.machine.DeleteDirectoryForFile(filename));
    }
}

TEST_F(MachineFixtureTest, DeleteExistingFileDirectory) {
    std::string filename = "file1.txt";

    mtest.machine.CreateDirectoryForFile(filename);

    auto status = std::filesystem::exists("/etc/db/versions/file1/");
    if (status) {
        EXPECT_FALSE(mtest.machine.DeleteDirectoryForFile(filename));
    }
}

