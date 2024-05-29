#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <iomanip>
#include "delimiter.hpp"

namespace bredyuk
{
    struct DataStruct
    {
        double key1;
        unsigned long long key2;
        std::string key3;
    };

    std::istream& operator>>(std::istream& is, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& is, DoubleIO&& dest);
    std::istream& operator>>(std::istream& is, UnsignedLongLongIO&& dest);
    std::istream& operator>>(std::istream& is, StringIO&& dest);
    std::istream& operator>>(std::istream& is, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);
    bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif