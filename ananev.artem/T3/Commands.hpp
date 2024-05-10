#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Struct.hpp"
#include <limits>
#include <iomanip>

namespace ananev
{
  void error(std::istream &in);
  double get_sum(double result, const Polygon& polygon, std::size_t param);
  double get_area(std::size_t param, const std::vector< ananev::Polygon > polygons);
  double get_max(std::size_t param, const std::vector< ananev::Polygon > polygons);
  double get_min(std::size_t param, const std::vector< ananev::Polygon > polygons);
  std::size_t get_count(std::size_t param, const std::vector< ananev::Polygon > polygons);

  void area_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void max_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void min_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void count_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
}

#endif
