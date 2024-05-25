#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iostream>

namespace semzin
{
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios<char> &s);
    ~iofmtguard();

  private:
    std::basic_ios<char> &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;
  };
}
#endif
