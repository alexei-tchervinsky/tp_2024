#ifndef COMPARE_HPP
#define COMPARE_HPP

#include "DataStruct.h"

namespace grudov
{
  struct Compare
  {
    bool operator()(Data first, Data second) const;
  };
}

#endif
