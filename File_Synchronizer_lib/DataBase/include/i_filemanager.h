#ifndef FILE_SYNCHRONIZER_I_FILEMANAGER_H
#define FILE_SYNCHRONIZER_I_FILEMANAGER_H

template <typename T>
class IFileManager {
public:
    virtual void Create(const T&) = 0;
    virtual void Delete(const T&) = 0;
    virtual void Update(const T&) = 0;
};

#endif //FILE_SYNCHRONIZER_I_FILEMANAGER_H
