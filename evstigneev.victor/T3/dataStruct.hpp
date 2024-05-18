#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <iostream>
#include <vector>

namespace evstigneev
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector<Point> points;
  };

  /*struct CArea
  {
    Point point_;
    double operator()(double d, Point& p1, Point& p2);
  };

  struct CAngle
  {
    Point point_1, point_2;
    bool operator()(Point& p_);
  };*/

  std::istream& operator>>(std::istream& in, evstigneev::Point& dest);
  std::istream& operator>>(std::istream& in, evstigneev::Polygon& poly);
  //std::ostream& operator<<(std::ostream& out, evstigneev::Polygon& poly);
}
#endif
