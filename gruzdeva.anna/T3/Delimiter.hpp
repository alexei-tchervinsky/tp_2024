#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iostream>

namespace shapes {
    struct DelimiterIO {
        char exp;
    };

    std::istream & operator>>(std::istream & is, DelimiterIO && d);
}


#endif //DELIMETER_HPP
