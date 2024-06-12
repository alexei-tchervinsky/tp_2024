#include "Comparing.hpp"

namespace AliKN {
    bool Comparator::operator()(const DataStruct& first, const DataStruct& second) const {
        if (first.key1 != second.key1) {
            return first.key1 < second.key1;
        }
        else if (first.key2 != second.key2) {
            return first.key2 < second.key2;
        }
        return first.key3.length() < second.key3.length();
    }
}
