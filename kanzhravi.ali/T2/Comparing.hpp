#ifndef COMPARING_HPP
#define COMPARING_HPP

#include "DataStruct.hpp"
#include <algorithm>

namespace AliKN {
    struct Comparator {
        bool operator()(const DataStruct& first, const DataStruct& second) const;
    };
}

#endif
