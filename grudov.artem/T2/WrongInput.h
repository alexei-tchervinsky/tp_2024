#ifndef WRONGINPUT_HPP
#define WRONGINPUT_HPP

#include <exception>

namespace grudov
{
  class WrongInput : public std::exception
  {
  public:
    WrongInput();
    const char* what_() const noexcept;
  private:
    const char* reason_;
  };
}

#endif