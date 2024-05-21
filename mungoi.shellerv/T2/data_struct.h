#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <string>
#include <iostream>

namespace mungoi
{
    struct DataStruct
    {
        double key1;
        long long key2;
        std::string key3;
    };

    std::string fromDoubleToScientific(double val);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

#endif
