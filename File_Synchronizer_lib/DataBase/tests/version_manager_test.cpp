#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <chrono>
#include <thread>

#include "versionmanager.h"
#include "versioncreator.h"
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

class TestVersionJournal : public ITransactionJournal {
private:
    std::vector<Transaction> log;
public:
    void AddTransaction(Transaction _tr) override {
        _tr.SetMessage(std::get<std::filesystem::path>(_tr.GetParams()));
        log.push_back(_tr);
    };
    std::filesystem::path GetLastTransaction() {
        return log.back().GetMessage();
    }
    void DeleteLastTransaction () override {
        log.pop_back();
    }
};

class FakeVersionCreator : public VersionCreator {
public:
    std::filesystem::path AddToIndex(const std::filesystem::path& sourceFilePath, const std::filesystem::path& versionsDirectory) override {
        std::string index = "index" + sourceFilePath.extension().string();
        return sourceFilePath.parent_path() / sourceFilePath.stem() / index;
    }
    std::filesystem::path CreateDiff(const std::filesystem::path& sourceFilePath, const std::filesystem::path& versionsDirectory) override {
        std::string version = HashIsFileContent(sourceFilePath) + sourceFilePath.extension().string();
        return sourceFilePath.parent_path() / sourceFilePath.stem() / version;
    }
};

class MockVersionCreator : public VersionCreator {
private:
    FakeVersionCreator fake;
public:
    typedef std::filesystem::path path;
    MOCK_METHOD(path, AddToIndex, (const path&, const path&), (override));
    MOCK_METHOD(path, CreateDiff, (const path&, const path&), (override));

    void DelegateToFake() {
        ON_CALL(*this, AddToIndex).WillByDefault([this](const path& source, const path& directory){
          return fake.AddToIndex(source, directory);
        });
        ON_CALL(*this, CreateDiff).WillByDefault([this](const path& source, const path& directory){
          return fake.CreateDiff(source, directory);
        });
    }
};

TEST_F(VersionTests, CreateVesionInManager) {
    File file(source);
    MockVersionCreator vCreator;
    TestVersionJournal tLogger;

    vCreator.DelegateToFake();

    VersionManager vManager(&tLogger, &vCreator);
    vManager.SetVersionsPath(source.parent_path());

    using ::testing::_;
    EXPECT_CALL(vCreator, AddToIndex(_, _));
    EXPECT_CALL(vCreator, CreateDiff(_, _));

    std::string testContent = "TESTFILE";
    fileWrite(source, testContent);

    vManager.CreateVersion(file);

    EXPECT_EQ("index" + source.extension().string(), tLogger.GetLastTransaction().filename().string());
    tLogger.DeleteLastTransaction();
    EXPECT_EQ(testContent + source.extension().string(), tLogger.GetLastTransaction().filename().string());
}

TEST_F(VersionTests, DeleteVesionInManager) {
    File file(source);
    MockVersionCreator vCreator;
    TestVersionJournal tLogger;

    vCreator.DelegateToFake();

    VersionManager vManager(&tLogger, &vCreator);
    vManager.SetVersionsPath(source.parent_path());

    using ::testing::_;
    EXPECT_CALL(vCreator, AddToIndex(_, _));
    EXPECT_CALL(vCreator, CreateDiff(_, _));

    std::string testContent = "TESTFILE";
    fileWrite(source, testContent);

    vManager.CreateVersion(file);
    tLogger.DeleteLastTransaction();

    fileWrite(tLogger.GetLastTransaction(), "");

    int countDeleted = 0;
    countDeleted = vManager.DeleteVersion(testFile, testContent + source.extension().string());
    EXPECT_NE(countDeleted, 0);
}

TEST_F(VersionTests, GetFileHistory) {
    File file(source);
    TestVersionJournal tLogger;

    VersionManager vManager(&tLogger);
    vManager.SetVersionsPath(source.parent_path());

    std::string firstSequence = "FIRST";
    std::string secondSequence = "SECOND";

    fileWrite(source, firstSequence);
    vManager.CreateVersion(file);

    // Для разницы во времени создания версии
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(1s);

    fileWrite(source, secondSequence);
    vManager.CreateVersion(file);

    std::vector<std::filesystem::path> history = vManager.GetVersionHistoryForFile(source.stem().string(), "*");
    fileRead(history[0]);
    EXPECT_EQ(message, firstSequence);
    fileRead(history[1]);
    EXPECT_EQ(message, secondSequence);
}