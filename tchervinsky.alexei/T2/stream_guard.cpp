#include "stream_guard.hpp"
#include <iostream>

tchervinsky::StreamGuard::StreamGuard(std::basic_ios<char> &s) :
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{
}

tchervinsky::StreamGuard::~StreamGuard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}
