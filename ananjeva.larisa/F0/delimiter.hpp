#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>
#include <string>

namespace ananjeva {
  struct DelimiterIO {
    char expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}

#endif
