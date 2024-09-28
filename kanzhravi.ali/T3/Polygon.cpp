#include "Polygon.hpp"
#include <iostream>

namespace AliKn
{
    std::istream& operator>>(std::istream& in, IOSeparator&& dummy)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '\0';
        in >> c;
        if (in && (c != dummy.del))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Point& dummy)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Point point;
        in >> IOSeparator{ '(' };
        in >> point.x;
        in >> IOSeparator{ ';' };
        in >> point.y;
        in >> IOSeparator{ ')' };
        dummy = point;
        return in;
    }

    std::istream& operator>>(std::istream& in, Polygon& dummy)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Polygon polygon;
        std::size_t vertexes;
        if (!(in >> vertexes))
        {
            in.setstate(std::ios::failbit);
        }
        Point point;
        for (std::size_t i = 0; i < vertexes; ++i)
        {
            in >> point;
            if (in)
            {
                polygon.points.push_back(point);
            }
        }

        if (vertexes != polygon.points.size() || polygon.points.size() < 3)
        {
            in.setstate(std::ios::failbit);
        }
        dummy = polygon;
        return in;
    }
}
