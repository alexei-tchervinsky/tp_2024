#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "dataStruct.hpp"

namespace evstigneev
{
  void area(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out);
  void max(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out);
  void min(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out);
  void count(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out);
  void lessArea(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out);
  void mxSeq(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out);
  /*size_t isEqualCount(const Polygon& poly,
    const std::vector<Point>& src, size_t& c);*/
}

#endif
