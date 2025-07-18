//
//  sstable.cpp
//  LevelDb
//
//  Created by 张宗煜 on 2025/7/15.
//

#include "sstable.hpp"
#include <iostream>

// 构造函数，打开输出文件
SstableWriter::SstableWriter(const std::string& filename) {
    outFile.open(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
    }
}

// 添加键值对
void SstableWriter::add(const std::string& key, const std::string& value) {
    if (!outFile.is_open()) {
        std::cerr << "文件未打开，无法写入" << std::endl;
        return;
    }

    // 简单把 key 和 value 拼接进 blockBuffer 里，格式可根据需求设计
    // 这里用 '\0' 作为分隔符示范（实际SSTable可能是二进制序列化）
    blockBuffer.append(key);
    blockBuffer.push_back('\0');
    blockBuffer.append(value);
    blockBuffer.push_back('\0');

    // 如果缓冲区大小达到一定阈值，就写入文件（这里阈值设100字节举例）
    if (blockBuffer.size() >= 100) {
        flushBlock();
    }
}

// 把缓冲区写入文件，并清空缓冲区
void SstableWriter::flushBlock() {
    if (!outFile.is_open()) {
        std::cerr << "文件未打开，无法写入" << std::endl;
        return;
    }
    if (blockBuffer.empty()) return;

    outFile.write(blockBuffer.data(), blockBuffer.size());
    if (!outFile) {
        std::cerr << "写入文件失败" << std::endl;
    }

    // 这里可以记录索引信息（模拟）
    // indexBlock.push_back({lastKey, offset}); // 具体实现视设计而定

    blockBuffer.clear();
}

// 结束写入，写入剩余缓冲区，关闭文件
void SstableWriter::finish() {
    flushBlock();
    if (outFile.is_open()) {
        outFile.close();
    }
}

// 构造函数，初始化输入文件流
SstableReader::SstableReader(const std::string& filename) {
    inFile.open(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
    }
    position = 0;
}
