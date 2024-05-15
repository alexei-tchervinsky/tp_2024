#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
#include <iostream>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& ds);
std::ostream& operator<<(std::ostream& os, const DataStruct& ds);
bool operator<(const DataStruct& a, const DataStruct& b);

#endif // DATA_STRUCT_H
