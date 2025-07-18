#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

namespace util {
    std::string serialize(const std::string& key, const std::string& value);
    void deserialize(const std::string& data, std::string& key, std::string& value);
    uint32_t crc32(const std::string& data);
}

#endif // UTIL_HPP
