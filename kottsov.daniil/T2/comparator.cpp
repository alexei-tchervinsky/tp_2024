#include "comparator.h"

namespace lst
{
  bool DataComparator::operator()(Data a, Data b) const
  {
    if (a.key1!=b.key1)
    {
      return a.key1 < b.key1;
    }
    else if (a.key2!=b.key2)
    {
      return a.key2 < b.key2;
    }
    else
    {
      return a.key3.length() < b.key3.length();
    }
  }
}

