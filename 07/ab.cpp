#include "fs.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstdint>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

using std::uint32_t;

Directory root("root", nullptr);
std::shared_ptr<Directory> current(&root);

void processCommand(std::string& cmd)
{
    std::stringstream ss(cmd);
    std::string token;
    ss.ignore(2, ' ');
    bool arg = false;
    while(std::getline(ss, token, ' '))
    {
        // ls lists out the files and directories contained within our directory
        if(token == "ls")
            break;

        // cd changes the directory
        if(!arg && token == "cd")
        {
            arg = true;
            continue;
        }

        // we are now processing the argument
        // if .., then move up the directory
        if(token == "..")
        {
            current = current->parent;
        }
        else
        {
            if(current->directoryExists(token))
            {
                current = current->getDirectory(token);
            }
        }
    }
}

void createFile(std::string &name, uint32_t size)
{
    auto file = std::shared_ptr<File>(new File(name, size));
    current->files.push_back(file);
}

void createDir(std::string &name)
{
    auto dir = std::shared_ptr<Directory>(new Directory(name, current));
    current->directories.push_back(dir);
}

void processFile(std::ifstream &in)
{
    std::string str;
    uint32_t counter = 0;

    // ignore first line
    in.ignore(LONG_MAX, '\n');

    while(std::getline(in, str))
    {
        std::stringstream lineReader(str);
        std::string token;

        bool isName = false;
        bool isDir = false;
        uint32_t fileSize = 0;

        while(std::getline(lineReader, token, ' '))
        {
            if(token == "$")
            {
                // break into command function
                processCommand(str);
                break;
            }

            if(isName)
            {
                if(isDir)
                    createDir(token);
                else
                    createFile(token, fileSize);

                break;
            }

            if(!isName && token == "dir")
            {
                isName = isDir = true;
                continue;
            }

            // must be filesize
            fileSize = static_cast<uint32_t>(std::stoul(token));
            isName = true;
        }
    }
}

void checkDirSize(std::shared_ptr<Directory> dir, std::vector<std::shared_ptr<Directory>> &list, uint32_t maxSize = 100000)
{
    // If this dir matches, then we are good
    if(dir->getFileSize() <= maxSize)
    {
        list.push_back(dir);
    }

    // Check each folder in our directory
    for(auto dir: dir->directories)
    {
        checkDirSize(dir, list, maxSize);
    }
}

void compareDirSize(std::shared_ptr<Directory> dir, uint32_t &current, uint32_t requiredSpace = 100000)
{
    // If this dir matches, then we are good
    if(dir->getFileSize() >= requiredSpace)
    {
        if(dir->getFileSize() < current)
        {
            current = dir->getFileSize();
        }
    }

    // Check each folder in our directory
    for(auto dir: dir->directories)
    {
        compareDirSize(dir, current, requiredSpace);
    }
}

uint32_t partA(uint32_t maxSize = 100000)
{
    std::vector<std::shared_ptr<Directory>> criterion;
    auto base = std::make_shared<Directory>(root);
    checkDirSize(base, criterion, maxSize);

    uint32_t result = 0;
    for(auto dir : criterion)
    {
        result += dir->getFileSize();
    }

    return result;
}

uint32_t partB(uint32_t diskSpace = 70000000, uint32_t requiredSpace = 30000000)
{
    auto neededSpace = requiredSpace - (diskSpace - root.getFileSize());
    auto base = std::make_shared<Directory>(root);
    uint32_t smallest = 0xffffffff;
    compareDirSize(base, smallest, neededSpace);

    return smallest;
}

int main(void)
{
    auto start_tree = Clock::now();
    // Open the file
    std::ifstream in("input.txt");
    if(!in)
    {
        std::cerr << "There was an error opening the input file." << std::endl;
        return 1;
    }
    processFile(in);
    in.close();
    auto end_tree = Clock::now();

    auto start_a = Clock::now();
    // Find all directories with maxsize=100000
    uint32_t resultA = partA(100000);
    std::cout << "Part A sum: " << resultA << std::endl;
    auto end_a = Clock::now();

    auto start_b = Clock::now();
    uint32_t smallestDir = partB(70000000, 30000000);
    std::cout << "Part B size: " << smallestDir << std::endl;
    auto end_b = Clock::now();

    std::cout << "Timings: \n";
    std::cout << "\tTree:  " << std::chrono::duration_cast<std::chrono::microseconds>(end_tree - start_tree).count() << " us\n";
    std::cout << "\tA:     " << std::chrono::duration_cast<std::chrono::microseconds>(end_a - start_a).count() << " us\n";
    std::cout << "\tB:     " << std::chrono::duration_cast<std::chrono::microseconds>(end_b - start_b).count() << " us\n";
    std::cout << "\tTotal: " << std::chrono::duration_cast<std::chrono::microseconds>(end_b - start_tree).count() << " us\n";
    return 0;
}