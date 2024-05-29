#include "WrongInput.h"

namespace grudov
{
  WrongInput::WrongInput() : reason_("Bad input") {};

  const char* WrongInput::what_() const noexcept{
    return reason_;
  }
}