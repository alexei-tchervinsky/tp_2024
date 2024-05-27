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
  std::size_t seq(std::vector<evstigneev::Polygon>::const_iterator begin,
    std::vector<evstigneev::Polygon>::const_iterator end, const Polygon& param);
}

#endif
