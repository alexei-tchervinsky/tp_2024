#ifndef SCOPEGUARD_HPP
#define SCOPEGUARD_HPP
#include <ios>

namespace lelkov
{
  class StreamGuard
  {
  public:
    explicit StreamGuard(std::basic_ios< char > &s) noexcept;
    ~StreamGuard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
