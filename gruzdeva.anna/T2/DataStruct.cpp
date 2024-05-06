#include "DataStruct.hpp"

#include <iomanip>

namespace ds {
  bool operator<(const DataStruct& rhs, const DataStruct& lhs) {
    if (rhs.key1 != lhs.key1)
      return rhs.key1 < lhs.key1;
    if (rhs.key2 != lhs.key2)
      return rhs.key2 < lhs.key2;
    return rhs.key3.length() < lhs.key3.length();
  }

  std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::istream::sentry s(is);
    if (!s)
      return is;

    is >> DelimiterIO{ '(' };
    for (std::size_t i = 0; i < 3; i++) {
      is >> DelimiterIO{ ':' };
      std::string key;
      is >> key;
      if (key == "key1") {
        is >> DoubleLitIO{ ds.key1 };
      }
      else if (key == "key2") {
        is >> ULLLitIO{ds.key2};
      }
      else if (key == "key3") {
        is >> StringIO{ds.key3};
      }
      if(!s) {
        return is;
      }
    }
    is >> DelimiterIO{ ')' };
    if (!is)
      is.setstate(std::ios_base::failbit);
    return is;
  }

  std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    os << "(:key1 " << std::fixed << std::setprecision(2) << ds.key1 << "d";
    os << ":key2 " << ds.key2 << "ull";
    os << ":key3 \"" << ds.key3 << "\")";
    return os;
  }


  std::istream & operator>>(std::istream & is, DelimiterIO && d) {
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

  std::istream & operator>>(std::istream & is, DoubleLitIO && dl) {
    std::istream::sentry s(is);
    if (!s)
      return is;
    int whole = 0;
    int decimal = 0;
    is >> whole >> DelimiterIO{ '.' } >> decimal;
    if (is.peek() == 'd')
      is >> DelimiterIO{ 'd' };
    else
      is >> DelimiterIO{'D'};
    int temp = decimal;
    double length = 1.0;
    while (temp > 0) {
      temp /= 10;
      length*=10.0;
    }
    dl.value = whole + (decimal / length);
    return is;
  }

  std::istream & operator>>(std::istream & is, ULLLitIO && ull) {
    std::istream::sentry s(is);
    if (!s)
      return is;
    unsigned long long value = 0;
    is >> value;
    if (is.peek() == 'u') {
      is >> DelimiterIO{'u'};
      is >> DelimiterIO{'l'};
      is >> DelimiterIO{'l'};
    }
    else {
      is >> DelimiterIO{'U'};
      is >> DelimiterIO{'L'};
      is >> DelimiterIO{'L'};
    }
    ull.value = value;
    return is;
  }

  std::istream & operator>>(std::istream & is, StringIO && str) {
    std::istream::sentry s(is);
    if (!s)
      return is;
    return std::getline(is >> DelimiterIO{'"'}, str.value, '"');
  }
}
