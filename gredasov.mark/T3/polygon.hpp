#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <iostream>
#include <vector>

namespace gredasov
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > pts;
  };

  std::istream & operator>>(std::istream & in, gredasov::Point & dest);
  std::istream & operator>>(std::istream & in, gredasov::Polygon & dest);
}

#endif

