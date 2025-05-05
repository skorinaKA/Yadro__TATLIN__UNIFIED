#ifndef FILE_TAPE_H
#define FILE_TAPE_H

#include "TapeInterface.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <filesystem>
#include <unordered_map>

using Config = std::unordered_map<std::string, int>;

class FileTape : public TapeInterface {
private:
    std::fstream fileStream;
    std::string filePath;

    Config config;

    int pos{0};
    int value{0};

public:
    FileTape(const std::string& path, Config &cfg)
        : filePath(path), config(cfg) {
        if(std::filesystem::exists(filePath)) fileStream.open(filePath, std::ios::in | std::ios::out);
        else fileStream.open(filePath, std::ios::in | std::ios::out | std::ios::trunc);
        if (!fileStream.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
    }

    FileTape(FileTape&& other) = default;
    FileTape& operator=(FileTape&& other) = default;

    ~FileTape() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    void write(int value) override {
        //std::this_thread::sleep_for(std::chrono::milliseconds(writeDelay));
        //fileStream.write(reinterpret_cast<char*>(&value), sizeof(int));
        fileStream << value << std::endl;
    }

    int read() override {
        //std::this_thread::sleep_for(std::chrono::milliseconds(readDelay));
        //fileStream.read(reinterpret_cast<char*>(&value), sizeof(int));
        fileStream >> value;
        return value;
    }

    bool hasMoreData() const override {
        return !fileStream.eof();
    }

    void shift(bool side) override {
        //std::this_thread::sleep_for(std::chrono::milliseconds(shiftDelay));
        side ? ++pos : --pos;
    }

    void rewind() override {
        //std::this_thread::sleep_for(std::chrono::milliseconds(rewindDelay));
        fileStream.clear(); // Clear eof flag
        fileStream.seekg(0, std::ios::beg);
    }
};

#endif // FILE_TAPE_H
