#ifndef DELIMITER_H
#define DELIMITER_H
#include <iostream>

namespace bekhova
{
  struct DelimiterIO
  {
    char del;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}
#endif
