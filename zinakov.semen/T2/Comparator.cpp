#include "Comparator.hpp"

namespace semzin
{
  bool Comparator::operator()(const Data first, const Data second) const
  {
    if (first.key1 != second.key1)
    {
      return (first.key1 < second.key1);
    }
    else if (first.key2 != second.key2)
    {
      return (first.key2 < second.key2);
    }
    return (first.key3.length() < second.key3.length());
  }
}
