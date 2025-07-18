#include "db.hpp"

DB::DB() {}
DB::~DB() {}

bool DB::put(const std::string& key, const std::string& value) { return false; }
bool DB::get(const std::string& key, std::string& value) { return false; }
bool DB::del(const std::string& key) { return false; }

void DB::flush() {}
void DB::recover() {}
void DB::compaction() {}
