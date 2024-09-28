#include "struct.hpp"

namespace nspace
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '\0';
        in >> c;
        if (in && (c != dest.del))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Point& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Point temp_point{};
        in >> temp_point.x;
        in >> DelimiterIO{ ';' };
        in >> temp_point.y;
        dest = temp_point;
        return in;
    }

    std::istream& operator>>(std::istream& in, Polygon& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::size_t count_points;
        in >> count_points;
        if (count_points < 3)
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        Polygon temp_polygon;
        for (size_t i = 0; i < count_points; i++)
        {
            Point temp_point;
            in >> DelimiterIO{ '(' };
            in >> temp_point;
            in >> DelimiterIO{ ')' };
            temp_polygon.points.push_back(temp_point);
        }
        if (in && count_points == temp_polygon.points.size())
        {
            dest = temp_polygon;
        }
        return in;
    }

    double area(const Polygon& polygon)
    {
        double area = 0;
        std::size_t count_points = polygon.points.size();
        for (std::size_t point = 0; point < count_points; point++)
        {
            if (point == count_points - 1)
            {
                area += (polygon.points[point].x * polygon.points[0].y - polygon.points[point].y *
                    polygon.points[0].x);
            }
            else
            {
                area += (polygon.points[point].x * polygon.points[point + 1].y - polygon.points[point].y *
                    polygon.points[point + 1].x);
            }
        }
        return 0.5 * abs(area);
    }
}
