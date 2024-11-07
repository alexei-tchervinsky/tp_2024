#ifndef COMPARE_HPP
#define COMPARE_HPP
#include <algorithm>
#include "Struct.hpp"

namespace gritsaev
{
    struct Compare
    {
        bool operator()(DataStruct first, DataStruct second) const;
    };
}

#endif