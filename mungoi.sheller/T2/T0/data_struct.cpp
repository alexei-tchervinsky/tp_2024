#include "data_struct.h"
#include <sstream>
#include <iomanip>

std::istream& operator>>(std::istream& is, DataStruct& data) {
    char c;
    std::string field;
    while (is >> c >> field) {
        if (field == "key1") {
            double val;
            is >> val >> c;
            data.key1 = val;
        }
        else if (field == "key2") {
            long long val;
            is >> val >> c;
            data.key2 = val;
        }
        else if (field == "key3") {
            std::getline(is >> std::ws, data.key3, ':');
        }
        else {
            std::string tmp;
            std::getline(is >> std::ws, tmp, ':');
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "key1: " << std::fixed << std::setprecision(10) << data.key1
        << " key2: " << data.key2 << " key3: \"" << data.key3 << "\"";
    return os;
}

bool operator<(const DataStruct& a, const DataStruct& b) {
    if (a.getKey1() != b.getKey1()) return a.getKey1() < b.getKey1();
    if (a.getKey2() != b.getKey2()) return a.getKey2() < b.getKey2();
    return a.getKey3() < b.getKey3();
}