#include "polygon_mungoi.h"
#include <numeric>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iterator>

namespace mungoisheller
{
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

    double get_area(std::size_t param, const std::vector<Polygon>& polygons)
    {
        std::function<double(double, const Polygon&)> BinaryOperation = std::bind(get_sum, std::placeholders::_1, std::placeholders::_2, param);
        if (param == 0)
        {
            return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, BinaryOperation) / polygons.size();
        }
        return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, BinaryOperation);
    }

    double get_max(std::size_t param, const std::vector<Polygon>& polygons)
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

    double get_min(std::size_t param, const std::vector<Polygon>& polygons)
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

    std::size_t get_count(std::size_t param, const std::vector<Polygon>& polygons)
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
        std::function<std::size_t(const Polygon&)> UnarOperation = std::bind([](const Polygon& a, std::size_t param)
            {
                return a.points.size() == param;
            }, std::placeholders::_1, param);
        return std::count_if(polygons.cbegin(), polygons.cend(), UnarOperation);
    }

    bool get_rects(const Point& start, const Point& end1, const Point& end2, const Point& end3)
    {
        Point vectors[3];
        vectors[0].x = end1.x - start.x;
        vectors[0].y = end1.y - start.y;
        vectors[1].x = end2.x - start.x;
        vectors[1].y = end2.y - start.y;
        vectors[2].x = end3.x - start.x;
        vectors[2].y = end3.y - start.y;
        bool angle01 = ((vectors[0].x * vectors[1].x + vectors[0].y * vectors[1].y) /
            (std::sqrt(std::pow(vectors[0].x, 2) + std::pow(vectors[0].y, 2)) * std::sqrt(std::pow(vectors[1].x, 2) + std::pow(vectors[1].y, 2)))) == 0;
        bool angle02 = ((vectors[0].x * vectors[2].x + vectors[0].y * vectors[2].y) /
            (std::sqrt(std::pow(vectors[0].x, 2) + std::pow(vectors[0].y, 2)) * std::sqrt(std::pow(vectors[2].x, 2) + std::pow(vectors[2].y, 2)))) == 0;
        bool angle12 = ((vectors[1].x * vectors[2].x + vectors[1].y * vectors[2].y) /
            (std::sqrt(std::pow(vectors[1].x, 2) + std::pow(vectors[1].y, 2)) * std::sqrt(std::pow(vectors[2].x, 2) + std::pow(vectors[2].y, 2)))) == 0;
        return angle01 || angle02 || angle12;
    }

    std::size_t get_seq(std::vector<Polygon>::const_iterator begin, std::vector<Polygon>::const_iterator end, const Polygon& param)
    {
        std::vector<Polygon>::const_iterator found = std::find(begin, end, param);
        return found != end ? std::distance(begin, found) : std::distance(begin, end);
    }

    void area_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return;
        }
        std::size_t param;
        in >> param;
        if (param == 0)
        {
            out << std::fixed << std::setprecision(1) << get_area(param, polygons) << "\n";
        }
        else
        {
            std::vector<Polygon> local_polygons;
            std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(local_polygons), [param](const Polygon& a)
                {
                    return a.points.size() == param;
                });
            if (local_polygons.empty())
            {
                out << "none\n";
            }
            else
            {
                out << std::fixed << std::setprecision(1) << get_area(param, local_polygons) << "\n";
            }
        }
    }

    void max_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return;
        }
        std::size_t param;
        in >> param;
        if (param == 0)
        {
            out << std::fixed << std::setprecision(1) << get_max(param, polygons) << "\n";
        }
        else
        {
            std::vector<Polygon> local_polygons;
            std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(local_polygons), [param](const Polygon& a)
                {
                    return a.points.size() == param;
                });
            if (local_polygons.empty())
            {
                out << "none\n";
            }
            else
            {
                out << std::fixed << std::setprecision(1) << get_max(param, local_polygons) << "\n";
            }
        }
    }

    void min_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return;
        }
        std::size_t param;
        in >> param;
        if (param == 0)
        {
            out << std::fixed << std::setprecision(1) << get_min(param, polygons) << "\n";
        }
        else
        {
            std::vector<Polygon> local_polygons;
            std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(local_polygons), [param](const Polygon& a)
                {
                    return a.points.size() == param;
                });
            if (local_polygons.empty())
            {
                out << "none\n";
            }
            else
            {
                out << std::fixed << std::setprecision(1) << get_min(param, local_polygons) << "\n";
            }
        }
    }

    void count_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return;
        }
        std::size_t param;
        in >> param;
        std::size_t result = get_count(param, polygons);
        if (result == 0)
        {
            out << "none\n";
        }
        else
        {
            out << result << "\n";
        }
    }

    void rects_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return;
        }
        std::size_t count = 0;
        for (auto& polygon : polygons)
        {
            if (polygon.points.size() == 4)
            {
                Point point1 = polygon.points[0];
                Point point2 = polygon.points[1];
                Point point3 = polygon.points[2];
                Point point4 = polygon.points[3];
                count += get_rects(point1, point2, point3, point4);
            }
        }
        if (count == 0)
        {
            out << "none\n";
        }
        else
        {
            out << count << "\n";
        }
    }

    void maxseq_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return;
        }
        Polygon param;
        in >> param;
        std::vector<Polygon>::const_iterator begin = polygons.cbegin();
        std::vector<Polygon>::const_iterator end = polygons.cend();
        std::size_t max_size = 0;
        std::size_t last_position = 0;
        std::size_t current_position = 0;
        std::vector<std::size_t> sizes;
        while (begin != end)
        {
            std::size_t count = get_seq(begin, end, param);
            if (count != static_cast<std::size_t>(std::distance(begin, end)))
            {
                sizes.push_back(count);
                if (max_size < count)
                {
                    max_size = count;
                    last_position = current_position;
                }
                current_position += count + 1;
                begin += count + 1;
            }
            else
            {
                sizes.push_back(count);
                break;
            }
        }
        if (max_size == 0)
        {
            out << "none\n";
        }
        else
        {
            out << last_position << " " << last_position + max_size << "\n";
        }
    }
}
