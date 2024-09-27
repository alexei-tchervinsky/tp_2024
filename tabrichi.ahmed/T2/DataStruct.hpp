#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>

struct DataStruct {
	unsigned long long key1 = 0;
	unsigned long long key2 = 0;
	std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& data);
std::ostream& operator<<(std::ostream& os, const DataStruct& data);

bool compareDataStruct(const DataStruct& a, const DataStruct& b);

#endif