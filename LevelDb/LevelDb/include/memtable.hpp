#ifndef MEMTABLE_HPP
#define MEMTABLE_HPP

#include <string>
#include <vector>

class SkipList {
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

    void put(const std::string& key, const std::string& value);
    bool remove(const std::string& key);
    bool contains(const std::string& key);
    bool get(const std::string& key, std::string& value);
    void clear();
    void print();
    size_t size();
    bool isFull();
};

#endif // MEMTABLE_HPP
