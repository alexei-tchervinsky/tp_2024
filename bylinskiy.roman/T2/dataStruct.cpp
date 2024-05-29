#include "dataStruct.h"

bool bylinskiy::DataStruct::operator<(const DataStruct& other) const
{
    if (key1 != other.key1) {
        return key1 < other.key1;
    }
    if (key2 != other.key2) {
        return key2 < other.key2;
    }
    return key3 < other.key3;
}