#include <gtest/gtest.h>
#include <fstream>
#include <chrono>
#include <thread>

#include "VersionCreator.h"
#include "fileinit_for_tests.hpp"


TEST_F(VersionTests, CreateIndexByCopy) {
    std::string firstSequence = "FIRST";
    std::string secondSequence = "SECOND";

    std::filesystem::path pathToTestFile = source.parent_path().string() + "/" + source.stem().string()
                                            + "/index" + source.extension().string();

    fileWrite(source, firstSequence);
    fileRead(source);
    ASSERT_EQ(message, firstSequence);

    vCreator.AddToIndex(source, source.parent_path());
    fileRead(pathToTestFile);
    EXPECT_EQ(message, firstSequence);

    fileWrite(source, secondSequence);

    vCreator.AddToIndex(source, source.parent_path());
    fileRead(pathToTestFile);
    EXPECT_EQ(message, secondSequence);
}

TEST_F(VersionTests, CreateVersionByCopy) {
    std::string firstSequence = "FIRST";
    std::string secondSequence = "SECOND";

    std::vector<std::filesystem::path> history;

    fileWrite(source, firstSequence);
    fileRead(source);
    ASSERT_EQ(message, firstSequence);

    vCreator.CreateVersion(source, source.parent_path());

    // Для разницы во времени создания версии
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(1s);

    fileWrite(source, secondSequence);

    vCreator.CreateVersion(source, source.parent_path());

    for ( auto& item: std::filesystem::directory_iterator(source.parent_path() / source.stem()) ) {
        history.push_back(item);
    }
    std::sort(history.begin(), history.end(), [](const std::filesystem::path& l, const std::filesystem::path& r) {
      return (std::filesystem::last_write_time(l) < std::filesystem::last_write_time(r));
    });

    fileRead(history[0]);
    EXPECT_EQ(message, firstSequence);

    fileRead(history[1]);
    EXPECT_EQ(message, secondSequence);
}
