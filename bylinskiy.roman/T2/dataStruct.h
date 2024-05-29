#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iosfwd>
#include <string>

namespace bylinskiy {
    struct DataStruct {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;

        bool operator<(const DataStruct& other) const;
    };
}

#endif
