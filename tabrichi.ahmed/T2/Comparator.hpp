#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP
#include "DataStruct.hpp"
#include <algorithm>
namespace TAhm
{
    struct Comparator
    {
        bool operator()(const DataItem first, const DataItem second) const;
    };
}
#endif