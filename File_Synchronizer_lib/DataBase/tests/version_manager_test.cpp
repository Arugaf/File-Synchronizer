#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <chrono>
#include <thread>

#include "VersionManager.h"
#include "VersionCreator.h"
#include "fileinit_for_tests.hpp"

std::string HashIsFileContent(const std::filesystem::path& targetSource) {
    std::string content;

    std::ifstream targetFile(targetSource);
    if (targetFile.is_open()) {
        std::getline(targetFile, content);
    }
    targetFile.close();

    return content;
}

class FakeVersionCreator : public VersionCreator {
public:
    std::filesystem::path AddToIndex(const std::filesystem::path& sourceFilePath, const std::filesystem::path& versionsDirectory) override {
        return "index" + sourceFilePath.extension().string();
    }
    std::filesystem::path CreateVersion(const std::filesystem::path& sourceFilePath, const std::filesystem::path& versionsDirectory) override {
        std::string version = HashIsFileContent(sourceFilePath) + sourceFilePath.extension().string();
        return version;
    }
};

class MockVersionCreator : public VersionCreator {
private:
    FakeVersionCreator fake;
public:
    typedef std::filesystem::path path;
    MOCK_METHOD(path, AddToIndex, (const path&, const path&), (override));
    MOCK_METHOD(path, CreateVersion, (const path&, const path&), (override));

    void DelegateToFake() {
        ON_CALL(*this, AddToIndex).WillByDefault([this](const path& source, const path& directory){
          return fake.AddToIndex(source, directory);
        });
        ON_CALL(*this, CreateVersion).WillByDefault([this](const path& source, const path& directory){
          return fake.CreateVersion(source, directory);
        });
    }
};


TEST_F(VersionTests, CreateVesionInManager) {
    MockVersionCreator vCreator;

    vCreator.DelegateToFake();

    VersionManager vManager(source.parent_path(), &vCreator);

    std::string testContent = "TESTFILE";
    fileWrite(source, testContent);

    using ::testing::_;
    using ::testing::Return;
    EXPECT_CALL(vCreator, AddToIndex(_, _)).Times(1)
    .WillOnce(Return("index" + source.extension().string()));
    EXPECT_CALL(vCreator, CreateVersion(_, _)).Times(1)
    .WillOnce(Return(testContent + source.extension().string()));

    vManager.CreateVersion(source);
}


// -----
TEST_F(VersionTests, DeleteVesionInManager) {
    MockVersionCreator vCreator;

    vCreator.DelegateToFake();

    VersionManager vManager(source.parent_path(), &vCreator);

    using ::testing::_;
    EXPECT_CALL(vCreator, AddToIndex(_, _));
    EXPECT_CALL(vCreator, CreateVersion(_, _));

    std::string testContent = "TESTFILE";
    fileWrite(source, testContent);

    vManager.CreateVersion(source);

    std::string target = source.stem().string() + testContent + source.extension().string();
    fileWrite(source.parent_path() / "versions" / target, "");

    int countDeleted = 0;
    countDeleted = vManager.DeleteVersion(testFile, testContent + source.extension().string());
    EXPECT_NE(countDeleted, 0);
}

TEST_F(VersionTests, GetFileHistory) {
    VersionManager vManager(source.parent_path());

    std::string firstSequence = "FIRST";
    std::string secondSequence = "SECOND";

    fileWrite(source, firstSequence);
    vManager.CreateVersion(source);

    // Для разницы во времени создания версии
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(1s);

    fileWrite(source, secondSequence);
    vManager.CreateVersion(source);

    // Полная история файла
    std::vector<std::filesystem::path> history = vManager.GetVersionHistoryForFile(source);
    fileRead(history[0]);
    EXPECT_EQ(message, firstSequence);
    fileRead(history[1]);
    EXPECT_EQ(message, secondSequence);


    // Превышение по номеру версии отдаст последнюю версию
    history = vManager.GetVersionHistoryForFile(source, 15);
    fileRead(history[0]);
    EXPECT_EQ(message, secondSequence);
}

