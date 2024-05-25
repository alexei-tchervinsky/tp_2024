#include "geometryShapes.hpp"
#include "dataStruct.hpp"

std::istream& leontiev::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry se(in);
  if (!se)
  {
    return in;
  }
  using del = DelimiterIO;
  int x = 0;
  int y = 0;
  in >> del{'('} >> x >> del{';'} >> y >> del{')'};
  if (in)
  {
    dest.x = x;
    dest.y = y;
  }
  return in;
}

std::istream& leontiev::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry se(in);
  if (!se)
  {
    return in;
  }
  std::size_t vertexCounter = 0;
  if (!(in >> vertexCounter))
  {
    in.setstate(std::ios::failbit);
  }
  Point point;
  Polygon polygon;
  for (std::size_t i = 0; i < vertexCounter; ++i)
  {
    in >> point;
    if (in)
    {
      polygon.points.push_back(point);
    }
  }
  if (vertexCounter != polygon.points.size() || vertexCounter <= 2)
  {
    in.setstate(std::ios::failbit);
  }
  if (in)
  {
    dest = polygon;
  }
  return in;
}