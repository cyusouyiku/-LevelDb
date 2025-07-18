//
//  log.cpp
//  LevelDb
//
//  Created by 张宗煜 on 2025/7/14.
//

#include<fstream>
#include<string>
#include "log.hpp"


LogWriter::LogWriter(const std::string& path) {
    filePath = path;
    logFile.open(filePath, std::ios::app | std::ios::binary);
    if (!logFile.is_open()) {
        throw std::runtime_error("Fail to open target file:" + filePath);
    }
}

LogWriter::~LogWriter() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

bool LogWriter::isOpen() {
    return logFile.is_open();
}

void LogWriter::write(const std::string& key, const std::string& value) {
    uint32_t keyLen = key.size();
    uint32_t valueLen = value.size();
    logFile.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
    logFile.write(reinterpret_cast<const char*>(&valueLen), sizeof(valueLen));
    logFile.write(key.data(), keyLen);
    logFile.write(value.data(), valueLen);
}

void LogWriter::flush() {
    logFile.flush();
}

std::string LogWriter::currentLogFile() {
    return filePath;
}
