#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace shapes {
    struct Point {
        int x, y;
    };

    struct Polygon {
      std::vector<Point> points;
    };

    std::istream & operator>>(std::istream & is, Point & point);
    bool operator==(const Point& lhs, const  Point& rhs);
    int getX(const Point& point);
    int getY(const Point& point);

    std::istream & operator>>(std::istream & is, Polygon & poly);
    std::ostream & operator<<(std::ostream & os, const Polygon & poly);
    bool operator==(const Polygon& lhs, const Polygon& rhs);
    double getShapeArea(const Polygon & poly);
}

#endif // POLYGON_HPP
