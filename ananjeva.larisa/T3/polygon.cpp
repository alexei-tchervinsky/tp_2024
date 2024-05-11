#include "polygon.hpp"
#include "delimiter.hpp"

std::istream& ananjeva::operator>>(std::istream& in, Point& dest) {
  std::istream::sentry guard(in);
  if (!guard) {
    return in;
  }
  int x = 0;
  int y = 0;
  in >> DelimiterIO{ '(' } >> x >> DelimiterIO{ ';' } >> y >> DelimiterIO{ ')' };
  if (in) {
    dest.x = x;
    dest.y = y;
  }
  return in;
}

std::istream& ananjeva::operator>>(std::istream& in, Polygon& dest) {
  std::istream::sentry guard(in);
  if (!guard) {
    return in;
  }
  std::size_t pointCount = 0;
  if (!(in >> pointCount) || (pointCount <= 2)) {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > polygon;
  Point point;
  for (std::size_t i = 0; i < pointCount; i++) {
    if (in.get() != ' ') {
      in.setstate(std::ios::failbit);
      return in;
    }
    if (in >> point) {
      polygon.push_back(point);
    }
  }
  if (in && polygon.size() == pointCount && in.get() == '\n') {
    dest = Polygon{ polygon };
  }
  else {
    in.setstate(std::ios::failbit);
  }
  return in;
}
