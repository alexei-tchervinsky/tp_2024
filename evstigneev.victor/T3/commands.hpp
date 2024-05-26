#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "dataStruct.hpp"

namespace evstigneev
{
  void area(const std::vector<evstigneev::Polygon>& poly);
  void max(const std::vector<evstigneev::Polygon>& poly);
  void min(const std::vector<evstigneev::Polygon>& poly);
  void count(const std::vector<evstigneev::Polygon>& poly);
  void lessArea(const std::vector<evstigneev::Polygon>& poly);
  void mxSeq(const std::vector<evstigneev::Polygon>& poly);
  size_t isEqualCount(const Polygon& poly,
    const std::vector< Point >& src, size_t& counter);
}

#endif
