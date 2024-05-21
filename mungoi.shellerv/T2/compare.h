#ifndef COMPARE_HPP
#define COMPARE_HPP
#include "data_struct.h"

namespace mungoi
{
    struct Compare
    {
        bool operator()(DataStruct first, DataStruct second) const;
    };
}

#endif