#include "Polygon.hpp"
#include "Delimiter.hpp"

#include <algorithm>
#include <numeric>

namespace shapes {
  std::istream &operator>>(std::istream &is, Point &point) {
    std::istream::sentry s(is);
    if (!s)
      return is;

    int x = 0;
    int y = 0;
    is >> DelimiterIO{'('};
    is >> x;
    is >> DelimiterIO{';'};
    is >> y;
    is >> DelimiterIO{')'};

    if (is) {
      point.x = x;
      point.y = y;
    }

    return is;
  }

  bool operator==(const Point &lhs, const Point &rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
  }

  int getX(const Point &point) {
    return point.x;
  }

  int getY(const Point &point) {
    return point.y;
  }

  std::istream &operator>>(std::istream &is, Polygon &poly) {
    std::istream::sentry s(is);
    if (!s)
      return is;
    std::size_t pointsCount = 0;
    is >> pointsCount;

    if (!is || pointsCount <= 2) {
      is.setstate(std::istream::failbit);
      return is;
    }

    Point point{};
    std::vector<Point> points;
    for (std::size_t i = 0; i < pointsCount; i++) {
      if (is.get() != ' ') {
        is.setstate(std::istream::failbit);
        return is;
      }
      if (is >> point) {
        points.push_back(point);
      } else {
        is.setstate(std::istream::failbit);
        return is;
      }
    }

    if (is.peek() != '\n') {
      is.setstate(std::istream::failbit);
    }

    if (points.size() == pointsCount) {
      poly = Polygon{points};
    } else {
      is.setstate(std::istream::failbit);
    }

    return is;
  }

  std::ostream & operator<<(std::ostream & os, const Polygon & poly) {
    os << poly.points.size() << " ";
    for (const auto &point : poly.points) {
      os << " (" << point.x << ";" << point.y << ")";
    }
    os << "\n";
    return os;
  }

  // find area of polygon using Shoelace formula
  double getShapeArea(const Polygon & poly) {
    double area = 0.0;
    std::vector<int> diffOfCoords(poly.points.size());
    std::transform(
        ++poly.points.cbegin(),
        poly.points.cend(),
        poly.points.cbegin(),
        diffOfCoords.begin(),
        [](const Point & p1, const Point & p2) { return p1.x * p2.y - p1.y * p2.x; }
        );
    diffOfCoords.push_back(poly.points.front().x * poly.points.back().y - poly.points.front().y * poly.points.back().x);
    area = std::accumulate(diffOfCoords.cbegin(), diffOfCoords.cend(), 0.0);
    area = std::abs(area) / 2.0;
    return area;
  }

  bool operator==(const Polygon& lhs, const Polygon& rhs) {
    return std::equal(
        std::begin(lhs.points), std::end(lhs.points),
        std::begin(rhs.points), std::end(rhs.points)
        );
  }
}
