#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include<string>
#include<iostream>

namespace ananjeva {
  struct DoubleIO {
    double& ref;
  };

  struct CharIO {
    char& ref;
  };

  struct StringIO {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::ostream& outputDoubleScience(std::ostream& out, double number);
}

#endif