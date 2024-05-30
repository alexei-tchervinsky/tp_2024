#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "Struct.h"

namespace grudov
{
  double get_sum(double result, const Polygon& polygon, std::size_t arg);
  double get_area(std::size_t arg, const std::vector< grudov::Polygon > polygons);
  double get_max(std::size_t arg, const std::vector< grudov::Polygon > polygons);
  double get_min(std::size_t arg, const std::vector< grudov::Polygon > polygons);
  std::size_t get_count(std::size_t arg, const std::vector< grudov::Polygon > polygons);
  bool get_rects(const Point& start, const Point& end1, const Point& end2, const Point& end3);
  std::size_t get_seq(std::vector< grudov::Polygon >::const_iterator begin,
  std::vector< grudov::Polygon >::const_iterator end, const Polygon& arg);

  void area(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out);
  void max(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out);
  void min(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out);
  void count(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out);
  void rects(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out);
  void maxseq(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out);
}

#endif
