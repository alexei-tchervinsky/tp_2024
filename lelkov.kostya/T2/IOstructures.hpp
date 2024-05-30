#ifndef IOSTRUCTURES_HPP
#define IOSTRUCTURES_HPP
#include <string>
#include <iosfwd>
#include "UllOctIO.hpp"
#include "UllLitIO.hpp"
#include "StringIO.hpp"
#include "DelimiterIO.hpp"
namespace lelkov
{
  std::istream & operator>>(std::istream & in, DelimiterIO && value);
  std::istream & operator>>(std::istream & in, UllLitIO && value);
  std::istream & operator>>(std::istream & in, UllOctIO && value);
  std::istream & operator>>(std::istream & in, StringIO && value);

  using Del = DelimiterIO;
  using UllLit = UllLitIO;
  using UllOct = UllOctIO;
  using Str = StringIO;
}

#endif
