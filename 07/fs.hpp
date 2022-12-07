#pragma once
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>

using std::uint32_t;

struct File
{
public:
    std::string name;
    uint32_t size;
    File(std::string name, uint32_t size) : name(name), size(size) {};
};

struct Directory
{
public:
    std::vector<std::shared_ptr<File>> files;
    std::vector<std::shared_ptr<Directory>> directories;
    std::string name;
    std::shared_ptr<Directory> parent;

    uint32_t getFileSize()
    {
        uint32_t result = 0;
        for(auto file : files)
        {
            result += file->size;
        }

        for(auto dir : directories)
        {
            result += dir->getFileSize();
        }

        return result;
    };

    bool directoryExists(std::string& name){
        for (auto dir: directories) {
            if(dir->name == name)
                return true;
        }
        return false;
    };

    std::shared_ptr<Directory> getDirectory(std::string& name){
        for(auto dir: directories) {
            if(dir->name == name)
                return dir;
        }

        return nullptr;
    };

    Directory(std::string name, std::shared_ptr<Directory> parent = nullptr) : name(name), parent(parent){};

    friend bool operator<(Directory &lhs, Directory &rhs) { return lhs.getFileSize() < rhs.getFileSize(); };
    friend bool operator>(Directory &lhs, Directory &rhs) { return rhs < lhs; };
    friend bool operator<=(Directory &lhs, Directory &rhs) { return !(lhs > rhs); };
    friend bool operator>=(Directory &lhs, Directory &rhs) { return !(lhs < rhs); };
};