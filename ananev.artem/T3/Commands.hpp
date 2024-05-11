#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Struct.hpp"
#include <limits>
#include <iomanip>
#include <exception>

namespace ananev
{
  double get_sum(double result, const Polygon& polygon, std::size_t param);
  double get_area(std::size_t param, const std::vector< ananev::Polygon > polygons);
  double get_max(std::size_t param, const std::vector< ananev::Polygon > polygons);
  double get_min(std::size_t param, const std::vector< ananev::Polygon > polygons);
  std::size_t get_count(std::size_t param, const std::vector< ananev::Polygon > polygons);
  bool get_rects(const Polygon& polygon);

  void area_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void max_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void min_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void count_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void rects_param(const std::vector< ananev::Polygon > polygons, std::ostream &out);
}

#endif
