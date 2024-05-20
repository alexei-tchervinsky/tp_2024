#ifndef COMPARE_HPP
#define COMPARE_HPP
#include "DataStruct.hpp"

namespace kabalin
{
  struct Compare
  {
    bool operator()(DataStruct first, DataStruct second) const;
  };
} // namespace kabalin

#endif

