#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "dataStruct.hpp"

namespace evstigneev
{
  std::ostream& area(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& max(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& min(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& count(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& lessArea(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& maxSeq(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
}

#endif
