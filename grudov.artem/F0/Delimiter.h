#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace grudov
{
    struct DelimiterIO
    {
      char del;
    };
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}
#endif
