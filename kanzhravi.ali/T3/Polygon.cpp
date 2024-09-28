#include "Polygon.hpp"
#include <iostream>

namespace AliKn
{
    std::istream& operator>>(std::istream& input, Polygon& shape)
    {
        std::istream::sentry sentry(input);
        if (!sentry)
        {
            return input;
        }
        Polygon tempo;
        std::size_t numVertexes;
        if (!(input >> numVertexes))
        {
            input.setstate(std::ios::failbit);
        }
        Point point;
        for (std::size_t i = 0; i < numVertexes; ++i)
        {
            input >> point;
            if (input)
            {
                tempo.points.push_back(point);
            }
        }

        if (numVertexes != tempo.points.size() || tempo.points.size() < 3)
        {
            input.setstate(std::ios::failbit);
        }
        shape = tempo;
        return input;
    }

    std::istream& operator>>(std::istream& input, Point& coord)
    {
        std::istream::sentry sentry(input);
        if (!sentry)
        {
            return input;
        }
        Point temp;
        input >> IOSeparator{ '(' };
        input >> temp.x;
        input >> IOSeparator{ ';' };
        input >> temp.y;
        input >> IOSeparator{ ')' };
        coord = temp;
        return input;
    }

    std::istream& operator>>(std::istream& input, IOSeparator&& ioSep)
    {

        std::istream::sentry sentry(input);
        if (!sentry)
        {
            return input;
        }
        char c = '\0';
        input >> c;
        if (input && (c != ioSep.del))
        {
            input.setstate(std::ios::failbit);
        }
        return input;
    }
}
