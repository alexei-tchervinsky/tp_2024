#include "functions.hpp"
#include <numeric>
#include <functional>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <exception>
#include <iterator>

namespace geometry
{
    std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
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

    std::istream &operator>>(std::istream &in, Point &dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Point temp_point;
        in >> temp_point.x;
        in >> DelimiterIO{';'};
        in >> temp_point.y;
        dest = temp_point;
        return in;
    }

    std::istream &operator>>(std::istream &in, Polygon &dest)
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
            in >> DelimiterIO{'('};
            in >> temp_point;
            in >> DelimiterIO{')'};
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
            if (point == count_points -1)
            {
                area += (polygon.points[point].x * polygon.points[0].y - polygon.points[point].y *
                polygon.points[0].x);
            }
           else
            {
                area += (polygon.points[point].x * polygon.points[point+1].y - polygon.points[point].y *
                polygon.points[point+1].x);
            }
        }
        return 0.5*abs(area);
    }

    double get_sum(double result, const Polygon& polygon, std::size_t param)
    {
        if (param == 0)
        {
            return result + area(polygon);
        }
        else if (param == 1 && polygon.points.size() % 2 != 0)
        {
            return result + area(polygon);
        }
        else if (param == 2 && polygon.points.size() % 2 == 0)
        {
            return result + area(polygon);
        }
        else if (param == polygon.points.size())
        {
            return result + area(polygon);
        }
        return result;
    }

    double get_area(std::size_t param, const std::vector< geometry::Polygon > polygons)
    {
        std::function< double(double, const Polygon&) > BinaryOperation = std::bind(get_sum,
        std::placeholders::_1,
        std::placeholders::_2,
        param);
        if (param == 0)
        {
            return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, BinaryOperation) / polygons.size();
        }
        return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, BinaryOperation);
    }

    double get_max(std::size_t param, const std::vector< geometry::Polygon > polygons)
    {
        if (param == 0)
        {
            return area(*std::max_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
            {
                return area(a) < area(b);
            }));
        }
        return std::max_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
        {
            return a.points.size() < b.points.size();
        })->points.size();
    }

    double get_min(std::size_t param, const std::vector< geometry::Polygon > polygons)
    {
        if (param == 0)
        {
            return area(*std::min_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
            {
                return area(a) < area(b);
            }));
        }
        return std::min_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
        {
            return a.points.size() < b.points.size();
        })->points.size();
    }

    std::size_t get_count(std::size_t param, const std::vector< geometry::Polygon > polygons)
    {
        if (param == 1)
        {
            return std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& a)
            {
                return a.points.size() % 2 != 0;
            });
        }
        else if (param == 2)
        {
            return std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& a)
            {
                return a.points.size() % 2 == 0;
            });
        }
        std::function< std::size_t(const Polygon&) > UnarOperation = std::bind([](const Polygon& a, std::size_t param)
        {
            return a.points.size() == param;
        },
        std::placeholders::_1,
        param);
        return std::count_if(polygons.cbegin(), polygons.cend(), UnarOperation);
    }

    bool get_rects(const Point& start, const Point& end1, const Point& end2, const Point& end3)
    {
        Point vectors[3];
        vectors[0].x = end1.x-start.x;
        vectors[0].y = end1.y-start.y;
        vectors[1].x = end2.x-start.x;
        vectors[1].y = end2.y-start.y;
        vectors[2].x = end3.x-start.x;
        vectors[2].y = end3.y-start.y;
        bool angle01 = ((vectors[0].x*vectors[1].x+vectors[0].y*vectors[1].y)/
        (sqrt(std::pow(vectors[0].x, 2)+std::pow(vectors[0].y, 2))*sqrt(std::pow(vectors[1].x, 2)+std::pow(vectors[1].y, 2))) == 0);
        bool angle02 = ((vectors[0].x*vectors[2].x+vectors[0].y*vectors[2].y)/
        (sqrt(std::pow(vectors[0].x, 2)+std::pow(vectors[0].y, 2))*sqrt(std::pow(vectors[2].x, 2)+std::pow(vectors[2].y, 2))) == 0);
        bool angle12 = ((vectors[2].x*vectors[1].x+vectors[2].y*vectors[1].y)/
        (sqrt(std::pow(vectors[2].x, 2)+std::pow(vectors[2].y, 2))*sqrt(std::pow(vectors[1].x, 2)+std::pow(vectors[1].y, 2))) == 0);
        return angle01 || angle02 || angle12;
    }
    std::size_t get_seq(std::vector< geometry::Polygon >::const_iterator begin,
    std::vector< geometry::Polygon >::const_iterator end, const Polygon& param)
    {
        bool repeat = true;
        std::function<bool(const Polygon&)> FindIfUO = std::bind([](const Polygon& polygon, const Polygon& param)
        {
            return (polygon == param);
        }, std::placeholders::_1, param);
        std::function<bool(const Polygon&)> CountIfUO = std::bind([](const Polygon& polygon, const Polygon& param, bool& repeat)
        {
            if (polygon == param && repeat == true)
            {
                return true;
            }
            repeat = false;
            return false;
        }, std::placeholders::_1, param, repeat);
        std::vector< geometry::Polygon >::const_iterator begin_new = std::find_if(begin, end, FindIfUO);
        if (begin_new != end)
        {
            std::size_t count_current = std::count_if(begin_new, end, CountIfUO);
            std::size_t count_next = get_seq(begin_new + count_current, end, param);
            if (count_current > count_next)
            {
                return count_current;
            }
            return count_next;
        }
        else
        {
            return 0;
        }
    }

    void area_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out)
    {
        std::string param;
        in >> param;
        try
        {
            if (param == "MEAN" && polygons.size() >= 1)
            {
                out << std::setprecision(1) << get_area(0, polygons) << '\n';
            }
            else if (param == "ODD")
            {
                out << std::setprecision(1) << get_area(1, polygons) << '\n';
            }
            else if (param == "EVEN")
            {
                out << std::setprecision(1) << get_area(2, polygons) << '\n';
            }
            else if (stoll(param) >= 3)
            {
                out << std::setprecision(1) << get_area(stoll(param), polygons)<< '\n';
            }
            else
            {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }
        catch(std::exception& ex)
        {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void max_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out)
    {
        std::string param;
        in >> param;
        if (param == "AREA" && polygons.size() >= 1)
        {
            out << std::setprecision(1) << get_max(0, polygons) << '\n';
        }
        else if (param == "VERTEXES" && polygons.size() >= 1)
        {
            out << std::setprecision(0) << get_max(1, polygons) << '\n';
        }
        else
        {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void min_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out)
    {
        std::string param;
        in >> param;
        if (param == "AREA" && polygons.size() >= 1)
        {
            out << std::setprecision(1) << get_min(0, polygons) << '\n';
        }
        else if (param == "VERTEXES" && polygons.size() >= 1)
        {
            out << std::setprecision(0) << get_min(1, polygons) << '\n';
        }
        else
        {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void count_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out)
    {
        std::string param;
        in >> param;
        try
        {
            if (param == "ODD")
            {
                out << std::setprecision(0) << get_count(1, polygons) << '\n';
            }
            else if (param == "EVEN")
            {
                out << std::setprecision(0) << get_count(2, polygons) << '\n';
            }
            else if (stoll(param) >= 3)
            {
                out << std::setprecision(0) << get_count(stoll(param), polygons) << '\n';
            }
            else
            {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }
        catch (std::exception& ex)
        {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void rects_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out)
    {
        if (!in)
        {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
        out << std::setprecision(0) << std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& polygon)
        {
            if (polygon.points.size()==4)
            {
                return get_rects(polygon.points[0], polygon.points[1], polygon.points[2], polygon.points[3]) &&
                get_rects(polygon.points[1], polygon.points[2], polygon.points[3], polygon.points[0]) &&
                get_rects(polygon.points[2], polygon.points[3], polygon.points[0], polygon.points[1]);
            }
            return false;
        }) << '\n';
    }

    void maxseq_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out)
    {
        Polygon param;
        in >> param;
        if (!in || in.peek() != '\n')
        {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
        out << std::setprecision(0) << get_seq(polygons.cbegin(), polygons.cend(), param) << '\n';
    }
}
