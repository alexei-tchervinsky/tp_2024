#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <string>
#include <iostream>

namespace ananjeva {
  struct DelimiterIO {
    char expected;
  };

  struct LabelIO {
    std::string expected;
 };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}

#endif
