#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>
#include <string>

namespace ananjeva {
  struct DelimiterIO {
    char expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

  struct LabelIO {
    std::string expected;
  };

  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}

#endif
