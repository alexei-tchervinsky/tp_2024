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
  std::size_t seq(std::vector< nspace::Polygon >::const_iterator b,
    std::vector< nspace::Polygon >::const_iterator e, const Polygon& poly)
}

#endif
