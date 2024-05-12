#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP
#include "DataStruct.hpp"
#include <algorithm>

namespace semzin
{
  struct Comparator
  {
    bool operator()(const Data first, const Data second) const;
  };
}

#endif
