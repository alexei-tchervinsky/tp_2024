#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <iostream>

namespace AliKn
{
    struct Point
    {
        int x, y;
    };

    struct Polygon
    {
        std::vector<Point> points;
    };

    struct IOSeparator
    {
        char del;
    };

    std::istream& operator>>(std::istream& in, IOSeparator&& dest);
    std::istream& operator>>(std::istream& in, Point& dest);
    std::istream& operator>>(std::istream& in, Polygon& dest);
}
#endif
