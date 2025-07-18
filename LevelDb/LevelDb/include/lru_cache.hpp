#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <string>
#include <unordered_map>
#include <list>

class LRUCache {
public:
    LRUCache(size_t capacity);
    ~LRUCache();

    void put(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string& value);
    void remove(const std::string& key);

private:
    // 缓存数据结构
};

#endif // LRU_CACHE_HPP
