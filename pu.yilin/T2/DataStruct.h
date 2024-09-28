#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>
#include "FormatGuard.h"

namespace Data {
    struct DataStruct {
        double key1 = 0.0;
        long long key2 = 0;
        std::string key3;
    };

    struct DelimiterIO {
        char exp;
    };
    struct DoubleIO {
        double &ref;
    };
    struct LitIO {
        long long &ref;
    };
    struct StringIO {
        std::string &ref;
    };
    struct LabelIO {
        std::string exp;
    };

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);

    std::istream &operator>>(std::istream &in, DoubleIO &&dest);

    std::istream &operator>>(std::istream &in, StringIO &&dest);

    std::istream &operator>>(std::istream &in, LabelIO &&dest);

    std::istream &operator>>(std::istream &in, DataStruct &dest);

    std::istream &operator>>(std::istream &in, LitIO &&dest);

    std::ostream &operator<<(std::ostream &out, const DataStruct &dest);

    bool operator<(const DataStruct &first, const DataStruct &second);
}

#endif
