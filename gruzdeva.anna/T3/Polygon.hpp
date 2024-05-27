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

    std::istream & operator>>(std::istream & is, Polygon & poly);
    std::ostream & operator<<(std::ostream & os, const Polygon & poly);
    double getShapeArea(const Polygon & poly);
}

#endif // POLYGON_HPP
