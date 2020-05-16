class VersionTests : public ::testing::Test {
protected:
    void fileWrite(const std::filesystem::path& _target, const std::string& _sequence) {
        if (!std::filesystem::exists(_target.parent_path())) {
            std::filesystem::create_directories(_target.parent_path());
        }
        fOut.open(_target);
        fOut << _sequence;
        fOut.close();
    }

    void fileRead(const std::filesystem::path& _target) {
        fRead.open(_target);
        std::getline(fRead, message);
        fRead.close();
    }

    void SetUp() override {
        relativePath /= testFile;
        source = std::filesystem::absolute(relativePath);

        std::filesystem::remove_all(source.parent_path());
        std::filesystem::create_directories(source.parent_path());
    }

    std::string message;
    VersionCreator vCreator;

    std::string testFile = "test.txt";
    std::filesystem::path relativePath = "sandbox";
    std::filesystem::path source;

    std::ofstream fOut;
    std::ifstream fRead;
};