#include "FileWatcher.hpp"
#include "IMediator.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <filesystem>
#include <fstream>

class MockMediator : public FileSynchronizer::IMediator {
public:
    MOCK_METHOD(void, Notify, (FileSynchronizer::EventType), (override));
};

using FileSynchronizer::FileWatcher;
using testing::Exactly;
namespace fs = std::filesystem;

TEST(FileWatcherBasicFeatures, BadPath) {
    EXPECT_THROW(FileWatcher("badpath/"), FileSynchronizer::FileWatcherException::InvalidPath);
}

TEST(FileWatcherBasicFeatures, CorrectPath) {
    std::string path("correct_path/");
    fs::create_directory(path);
    ASSERT_TRUE(fs::exists(path));

    EXPECT_NO_THROW(FileWatcher fw(path));

    fs::remove(path);
}

TEST(FileCreating, Directory) {
    std::string path("file_creating_new_dir/");
    fs::create_directory(path);
    ASSERT_TRUE(fs::exists(path));

    FileWatcher fw(path, 100);

    std::string new_dir("test_dir/");

    MockMediator mediator;
    EXPECT_CALL(mediator, Notify).Times(Exactly(0));

    fw.StartWatching(&mediator);
    ASSERT_TRUE(fw.IsWorking() && fw.IsWatching());

    fs::create_directory(path + new_dir);
    ASSERT_TRUE(fs::exists(path + new_dir));

    std::this_thread::sleep_for(std::chrono::milliseconds(101));

    fw.StopWatching();

    fs::remove_all(path);
}

TEST(FileCreating, File) {
    std::string path("file_creating_new_file/");
    fs::create_directory(path);
    ASSERT_TRUE(fs::exists(path));

    FileWatcher fw(path, 100);

    MockMediator mediator;
    EXPECT_CALL(mediator, Notify(FileSynchronizer::EventType::FSChanged)).Times(Exactly(1));

    fw.StartWatching(&mediator);
    ASSERT_TRUE(fw.IsWorking() && fw.IsWatching());

    std::string file("new_file.txt");
    std::ofstream fstream(path + file);
    fstream.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(101));

    fw.StopWatching();

    fs::remove_all(path);
}

TEST(FileCreating, Ignored) {
    std::string path("file_creating_ignored_file/");
    fs::create_directory(path);
    ASSERT_TRUE(fs::exists(path));

    FileWatcher fw(path, std::unordered_set<std::string>({path + "new_file.txt"}), 100);

    MockMediator mediator;
    EXPECT_CALL(mediator, Notify(FileSynchronizer::EventType::FSChanged)).Times(Exactly(0));

    fw.StartWatching(&mediator);
    ASSERT_TRUE(fw.IsWorking() && fw.IsWatching());

    std::string file("new_file.txt");
    std::ofstream fstream(path + file);
    fstream.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(101));

    fw.StopWatching();

    fs::remove_all(path);
}

TEST(ExistingFiles, Deleted) {
    std::string path("file_creating_ignored_file/");
    fs::create_directory(path);
    ASSERT_TRUE(fs::exists(path));

    std::unordered_map<std::string, std::pair<fs::file_time_type, fs::file_type>> old_files;
    old_files[path + "new_file.txt"] = std::make_pair(fs::last_write_time(path), fs::file_type::regular);
    FileWatcher fw(path, old_files, 100);

    MockMediator mediator;
    EXPECT_CALL(mediator, Notify(FileSynchronizer::EventType::FSChanged)).Times(Exactly(1));

    fw.StartWatching(&mediator);
    ASSERT_TRUE(fw.IsWorking() && fw.IsWatching());

    std::this_thread::sleep_for(std::chrono::milliseconds(101));

    fw.StopWatching();

    fs::remove_all(path);
}
