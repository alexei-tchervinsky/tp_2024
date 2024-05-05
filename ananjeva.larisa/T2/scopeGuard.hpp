#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP

#include <iostream>

namespace ananjeva {
  class iofmtguard {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
