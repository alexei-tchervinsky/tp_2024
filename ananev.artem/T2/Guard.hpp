#ifndef GUARD_HPP
#define GUARD_HPP
#include <iostream>

namespace ananev
{
  class Guard
  {
    public:
      Guard(std::basic_ios<char> &s);
      ~Guard();
    private:
      std::basic_ios<char> &s_;
      char fill_;
      std::streamsize precision_;
      std::basic_ios<char>::fmtflags fmt_;
  };
}

#endif
