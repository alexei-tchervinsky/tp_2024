#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace lelkov {
    struct DelimiterIO {
        char expected;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}

#endif
