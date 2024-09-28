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

    std::istream& operator>>(std::istream& input, IOSeparator&& ioSep);
    std::istream& operator>>(std::istream& input, Point& coord);
    std::istream& operator>>(std::istream& input, Polygon& shape);
}
#endif#pragma once
