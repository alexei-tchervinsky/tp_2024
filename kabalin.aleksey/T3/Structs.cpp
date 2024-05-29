#include "Structs.hpp"
#include <cmath>
namespace kabalin {
std::istream &operator>>(std::istream &input, Delimetr &&del) {
  std::istream::sentry sentry(input);
  if (!sentry)
    return input;
  char el;
  input >> el;
  if (!input || el != del.del)
    input.setstate(std::istream::failbit);
  return input;
}

std::istream &operator>>(std::istream &input, Point &point) {
  std::istream::sentry sentry(input);
  if (!sentry)
    return input;
  input >> Delimetr('(') >> point.x >> Delimetr(';') >> point.y >>
      Delimetr(')');
  return input;
}

std::istream &operator>>(std::istream &input, Polygon &data) {
  std::istream::sentry sentry(input);
  if (!sentry)
    return input;

  int cnt_tops;
  input >> cnt_tops;

  if (cnt_tops < 3) {
    input.setstate(std::istream::failbit);
    return input;
  }
  data.points.clear();
  data.points.resize(cnt_tops);
  for (auto &pnt : data.points)
    input >> pnt;
  return input;
}

std::ostream &operator<<(std::ostream &output, const Point &point) {
  std::ostream::sentry sentry(output);
  if (!sentry)
    return output;

  output << " (" << point.x << ";" << point.y << ")";
  return output;
}

std::ostream &operator<<(std::ostream &output, const Polygon &data) {
  std::ostream::sentry sentry(output);
  if (!sentry)
    return output;
  output << data.points.size();
  for (auto &pnt : data.points)
    output << pnt;
  return output;
}

// Ccalculating the area of a triangle using a determinant
double triangle_area(Point p1, Point p2, Point p3) {
  return 0.5 * abs(p1.y * (p3.x - p2.x) + p2.y * (p1.x - p3.x) +
                   p3.y * (p2.x - p1.x));
}

double Polygon::area(void) const {
  const Point pnt = points.at(0);
  Point next = points.at(1);
  auto result = [&pnt, &next](double sum, const Point &el) {
    sum += triangle_area(pnt, next, el);
    next = el;
    return sum;
  };
  return std::accumulate(points.begin() + 2, points.end(), 0.0, result);
}

bool Polygon::isSame(const Polygon &other) const {
  const double EPSILON = std::numeric_limits<double>::epsilon();

  if (points.size() != other.points.size())
    return false;

  std::vector<Point> sortedPoints1 = points;
  std::vector<Point> sortedPoints2 = other.points;

  std::sort(sortedPoints1.begin(), sortedPoints1.end());
  std::sort(sortedPoints2.begin(), sortedPoints2.end());

  for (size_t i = 0; i < points.size(); ++i) {
    if (std::abs(sortedPoints1[i].x - sortedPoints2[i].x) > EPSILON ||
        std::abs(sortedPoints1[i].y - sortedPoints2[i].y) > EPSILON)
      return false;
  }

  return true;
}

bool Polygon::operator==(Polygon &otherData) {
  if (points.size() != otherData.points.size())
    return false;
  else
    for (size_t i = 0; i < points.size(); ++i)
      if (points.at(i) != otherData.points.at(i))
        return false;
  return true;
}

bool Point::operator!=(Point &otherPoint) {
  return x != otherPoint.x || y != otherPoint.y;
}
} // namespace kabalin
