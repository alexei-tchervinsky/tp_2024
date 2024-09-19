#include "Cmp.hpp"

namespace AliKN {

    bool Cmp::operator()(const DataItem first, const DataItem second) const {
        if (first.attr1 != second.attr1) {
            return (first.attr1 < second.attr1);
        }
        else if (first.attr2 != second.attr2) {
            return (first.attr2 < second.attr2);
        }
        return (first.attr3.length() < second.attr3.length());
    }

}
