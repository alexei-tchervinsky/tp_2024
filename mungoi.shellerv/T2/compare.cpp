#include "compare.h"

namespace mungoi
{
    bool Compare::operator()(const DataStruct& first, const DataStruct& second) const
    {
        if (first.key1 != second.key1)
        {
            return first.key1 < second.key1;
        }
        if (first.key2 != second.key2)
        {
            return first.key2 < second.key2;
        }
        return first.key3 < second.key3;
    }
}
