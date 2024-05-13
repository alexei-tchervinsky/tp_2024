#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
#include <iostream>
#include <sstream>

class DataStruct {
public:
    DataStruct() : key1(0.0), key2(0), key3("") {}
    DataStruct(double k1, long long k2, const std::string& k3) : key1(k1), key2(k2), key3(k3) {}

    double getKey1() const { return key1; }
    long long getKey2() const { return key2; }
    const std::string& getKey3() const { return key3; }

    friend std::istream& operator>>(std::istream& is, DataStruct& data);
    friend std::ostream& operator<<(std::ostream& os, const DataStruct& data);
    friend bool operator<(const DataStruct& a, const DataStruct& b);

private:
    double key1;
    long long key2;
    std::string key3;
};

#endif // DATA_STRUCT_H
