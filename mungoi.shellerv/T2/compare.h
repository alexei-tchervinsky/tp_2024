#ifndef COMPARE_HPP
#define COMPARE_HPP
#include "data_struct.h"

namespace mungoi
{
    struct Compare
    {
        bool operator()(const DataStruct& first, const DataStruct& second) const;
    };
}

#endif
