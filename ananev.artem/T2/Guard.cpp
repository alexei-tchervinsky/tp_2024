 #include "Guard.hpp"

 namespace ananev
 {
  Guard::Guard(std::basic_ios< char > &s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  Guard::~Guard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
