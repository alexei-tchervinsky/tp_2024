#include "Delimiter.hpp"

namespace shapes {
  std::istream &operator>>(std::istream &is, DelimiterIO &&d) {
    std::istream::sentry s(is);
    if (!s)
      return is;
    char c = '0';
    is >> c;
    if (is && (c != d.exp)) {
      is.setstate(std::ios_base::failbit);
    }
    return is;
  }
}
