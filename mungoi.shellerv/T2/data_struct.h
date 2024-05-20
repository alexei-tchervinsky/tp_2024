#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;

    friend std::istream& operator>>(std::istream& in, DataStruct& data);
    friend std::ostream& operator<<(std::ostream& out, const DataStruct& data);
};

#endif // DATA_STRUCT_H
