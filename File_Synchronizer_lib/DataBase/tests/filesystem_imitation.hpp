#include <variant>
#include <vector>

class FSObject {
protected:
    std::string name;
public:
    virtual ~FSObject() = default;

    virtual std::string GetName() {
        return name;
    }
    virtual void SetName(const std::string& _name) {
        name = _name;
    }

    virtual std::string Show() = 0;
};

class FSFile: public FSObject {
private:
    std::string type;
    std::string content;
public:
    FSFile() = default;
    ~FSFile() override = default;

    virtual std::string GetType() {
        return type;
    }
    virtual void SetType(const std::string& _type) {
        type = _type;
    }

    void SetContent(const std::string& _contentOfFile) {
        content = _contentOfFile;
    }
    std::string GetContent() {
        return content;
    }

    std::string Show() override {
        return GetName() + "." + type;
    }
};

class FSDirectory: public FSObject {
private:
    std::vector<std::variant<FSDirectory, FSFile>> content;
public:
    ~FSDirectory() override = default;
    std::string Show() override {
        std::string dirTree = GetName() + ":\n";

        for (auto& item : content) {
            visit([&dirTree](auto& obj) {
              std::string include = "\t" + obj.Show() + "\n";
              dirTree += include;
            }, item);
        }
        return dirTree;
    }

    void Add(const std::variant<FSDirectory, FSFile>& child) {
        content.push_back(child);
    }
};