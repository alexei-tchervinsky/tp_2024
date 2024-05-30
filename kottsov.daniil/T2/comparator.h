#include "datastruct.h"
#include <algorithm>
#ifndef COMPARATOR
#define COPMARATOR
namespace lst
{
  struct DataComparator
  {
    bool operator()(Data a, Data b) const;
  };
}
#endif
