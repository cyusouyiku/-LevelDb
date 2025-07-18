//
//  immutable_memtable.hpp
//  LevelDb
//
//  Created by 张宗煜 on 2025/7/15.
//
#ifndef IMMUTABLE_MEMTABLE_HPP
#define IMMUTABLE_MEMTABLE_HPP
using namespace std;

class SkipList{
private:
    struct Node {
        std::string key;
        std::string value;
        std::vector<Node*> forward;
        bool deleted;

    public:
        Node(int level, const std::string& k, const std::string& v, bool del = false);
    };

    Node* head;
    int maxLevel;
    int currentLevel;
    float probability;
    size_t currentSize;
    size_t maxSize;

    int randomLevel();
    
public:
    SkipList(int maxL, float prob, size_t maxS);
    ~SkipList();
    bool get(const string& key, string& value);
    bool contains(const string& key);
    void clear();
    void print();
    size_t size();
    bool isFull();
};
#endif
