//
//  log.hpp
//  LevelDb
//
//  Created by 张宗煜 on 2025/7/14.
//

#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <string>

class LogWriter {
private:
    std::ofstream logFile;
    std::string filePath;

public:
    LogWriter(const std::string& path);
    ~LogWriter();
    bool isOpen();
    void write(const std::string& key, const std::string& value);
    void flush();
    std::string currentLogFile();
};

#endif
