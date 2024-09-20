#ifndef COMPARING_HPP
#define COMPARING_HPP
#include "DataStruct.hpp"
namespace AliKN {

    struct Comparing
    {
        bool operator()(const DataItem first, const DataItem second) const;
    };

}

#endif
