#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <algorithm>
#include <string>
#include <functional>
#include <numeric>
#include <vector>
#include <iostream>

#include "geometry.h"
#include "io.h"

namespace berezneva
{
  std::ostream& area(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  std::ostream& min(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  std::ostream& max(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  std::ostream& count(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  std::ostream& lessArea(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  std::ostream& intersect(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
}
#endif
