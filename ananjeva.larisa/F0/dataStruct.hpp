#ifndef DATA_STRUCT_HPP
#define dATA_STRUCT_HPP

#include <iostream>
#include <string>
#include <set>

namespace ananjeva {
  struct EngIO {
    std::string& eng;
  };

  struct RusIO {
    std::set< std::string >& rus;
  };

  struct DictIO {
    std::pair< std::string, std::set< std::string > > dictStr;
  };

  std::istream& operator>>(std::istream& in, RusIO&& dest);
  std::istream& operator>>(std::istream& in, EngIO&& dest);
  std::istream& operator>>(std::istream& in, DictIO& dest);
}

#endif
