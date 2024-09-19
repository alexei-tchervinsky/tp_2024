#ifndef CMP_HPP
#define CMP_HPP
#include "DStruct.hpp"
namespace AliKN {

    struct Cmp
    {
        bool operator()(const DataItem first, const DataItem second) const;
    };

}

#endif
