#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>
#include "Delimiter.h"

namespace lawrenced {
    struct DataStruct {
        double key1{};
        long long key2{};
        std::string key3{};

        bool operator<(const DataStruct& other) const {
            if (key1 != other.key1) return key1 < other.key1;
            if (key2 != other.key2) return key2 < other.key2;
            return key3.size() < other.key3.size();
        }
    };

    std::istream& operator>>(std::istream& in, DataStruct& ds);
    std::ostream& operator<<(std::ostream& out, const DataStruct& ds);
}

#endif


