#include "Compare.h"

namespace grudov
{
  bool Compare::operator()(Data first, Data second) const
  {
    if (first.key1 != second.key1)
    {
      return first.key1 < second.key1;
    }
    if (first.key2 != second.key2)
    {
      return first.key2 < second.key2;
    }
    return first.key3.length() < second.key3.length();
  }
}