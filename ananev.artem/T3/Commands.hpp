#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Struct.hpp"
#include <limits>
#include <iomanip>
#include <exception>
#include <iterator>

namespace ananev
{
  double get_sum(double result, const Polygon& polygon, std::size_t param);
  double get_area(std::size_t param, const std::vector< ananev::Polygon > polygons);
  double get_max(std::size_t param, const std::vector< ananev::Polygon > polygons);
  double get_min(std::size_t param, const std::vector< ananev::Polygon > polygons);
  std::size_t get_count(std::size_t param, const std::vector< ananev::Polygon > polygons);
  bool get_rects(const Point& start, const Point& end1, const Point& end2, const Point& end3);
  std::size_t get_seq(std::vector< ananev::Polygon >::const_iterator begin, std::vector< ananev::Polygon >::const_iterator end, const Polygon& param);

  void area_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void max_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void min_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void count_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void rects_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
  void maxseq_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out);
}

#endif
