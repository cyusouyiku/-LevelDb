//
//  sstable.hpp
//  LevelDb
//
//  Created by 张宗煜 on 2025/7/15.
//

#include <fstream>
#include <string>
#include <vector>
#include <utility>
class SstableWriter{
private:
    std::ofstream outFile;
    std::string blockBuffer;
    std::vector<std::pair<std::string, uint32_t>> indexBlock;
public:
    SstableWriter(const std::string& filename);
    void add(const std::string& key,const std::string& value);
    void flushBlock();
    void finish();
    
};
class SstableReader{
private:
    std::ifstream inFile;
    std::string indexBlock;
    int position;
public:
    SstableReader(const std::string& filename);
    std::string get(const std::string& key);
    void loadIndex(const std::string& indexBlockPath);
    std::string readBlock(uint32_t offset);
    
    struct Footer {
        uint32_t indexOffset;
        uint32_t indexSize;
    };
};
