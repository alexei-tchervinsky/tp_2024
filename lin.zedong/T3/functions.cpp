#include "functions.hpp"
#include <cmath>
#include <sstream>
#include <algorithm>

namespace geometry
{
    std::istream& operator>>(std::istream& in, Point& dest)
    {
        char sep1, sep2, sep3;
        if (in >> sep1 >> dest.x >> sep2 >> dest.y >> sep3
            && sep1 == '(' && sep2 == ',' && sep3 == ')')
        {
            return in;
        }
        in.setstate(std::ios::failbit);
        return in;
    }

    std::istream& operator>>(std::istream& is, Polygon& poly)
    {
        std::size_t count;
        if (is >> count)
        {
            poly.points.resize(count);
            for (auto& point : poly.points)
            {
                if (!(is >> point))
                {
                    is.setstate(std::ios::failbit);
                    break;
                }
            }
        }
        return is;
    }

    double Polygon::calculate_area() const
    {
        double area = 0.0;
        int n = points.size();
        for (int i = 0; i < n; ++i)
        {
            int j = (i + 1) % n;
            area += points[i].x * points[j].y;
            area -= points[j].x * points[i].y;
        }
        return std::abs(area) / 2.0;
    }

    void read_polygons(std::istream& in, std::vector<Polygon>& polygons)
    {
        std::string line;
        while (std::getline(in, line))
        {
            std::istringstream iss(line);
            Polygon poly;
            if (iss >> poly)
            {
                polygons.push_back(std::move(poly));
            }
        }
    }

    bool is_rectangle(const Polygon& poly)
    {
        if (poly.points.size() != 4) return false;
        const auto& p = poly.points;

        auto dist_sq = [](const Point& a, const Point& b)
        {
            return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
        };

        std::vector<double> dists =
        {
            static_cast<double>(dist_sq(p[0], p[1])),
            static_cast<double>(dist_sq(p[0], p[2])),
            static_cast<double>(dist_sq(p[0], p[3])),
            static_cast<double>(dist_sq(p[1], p[2])),
            static_cast<double>(dist_sq(p[1], p[3])),
            static_cast<double>(dist_sq(p[2], p[3]))
        };

        std::sort(dists.begin(), dists.end());

        return dists[0] == dists[1] && dists[2] == dists[3] && dists[4] == dists[5] && dists[0] + dists[2] == dists[4];
    }

    double get_area_sum(const std::vector<Polygon>& polygons, std::function<bool(const Polygon&)> pred)
    {
        double sum = 0.0;
        for (const auto& poly : polygons)
        {
            if (pred(poly))
            {
                sum += poly.calculate_area();
            }
        }
        return sum;
    }

    double get_mean_area(const std::vector<Polygon>& polygons)
    {
        double sum = 0.0;
        for (const auto& poly : polygons)
        {
            sum += poly.calculate_area();
        }
        return polygons.size() > 0 ? sum / polygons.size() : 0.0;
    }

    double get_extreme_area(const std::vector<Polygon>& polygons, bool find_max)
    {
        if (polygons.empty())
        {
            return -1.0;
        }
        auto cmp = [](const Polygon& a, const Polygon& b)
        {
            return a.calculate_area() < b.calculate_area();
        };
        auto it = find_max ? std::max_element(polygons.begin(), polygons.end(), cmp)
                           : std::min_element(polygons.begin(), polygons.end(), cmp);
        return it->calculate_area();
    }

    int get_count(const std::vector<Polygon>& polygons, std::function<bool(const Polygon&)> pred)
    {
        return std::count_if(polygons.begin(), polygons.end(), pred);
    }

    int get_extreme_vertex_count(const std::vector<Polygon>& polygons, bool find_max)
    {
        if (polygons.empty())
        {
            return -1;
        }
        auto cmp = [](const Polygon& a, const Polygon& b)
        {
            return a.points.size() < b.points.size();
        };
        auto it = find_max ? std::max_element(polygons.begin(), polygons.end(), cmp)
                           : std::min_element(polygons.begin(), polygons.end(), cmp);
        return it->points.size();
    }

    int count_rectangles(const std::vector<Polygon>& polygons)
    {
        return std::count_if(polygons.begin(), polygons.end(), is_rectangle);
    }

    int max_sequence(const std::vector<Polygon>& polygons, const Polygon& target)
    {
        int max_seq = 0;
        int current_seq = 0;
        for (const auto& poly : polygons)
        {
            if (poly == target)
            {
                current_seq++;
                max_seq = std::max(max_seq, current_seq);
            }
            else
            {
                current_seq = 0;
            }
        }
        return max_seq;
    }

    void area_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::string param;
        in >> param;

        double total_area = 0.0;

        if (param == "EVEN")
        {
            total_area = get_area_sum(polygons, [](const Polygon& poly) { return poly.points.size() % 2 == 0; });
        }
        else if (param == "ODD")
        {
            total_area = get_area_sum(polygons, [](const Polygon& poly) { return poly.points.size() % 2 != 0; });
        }
        else if (param == "MEAN")
        {
            if (polygons.empty())
            {
                out << "<INVALID COMMAND>" << std::endl;
                return;
            }
            total_area = get_mean_area(polygons);
        }
        else
        {
            try
            {
                int specified_vertices = std::stoi(param);
                if (specified_vertices < 3)
                {
                    out << "0.0" << std::endl;
                }
                else
                {
                    total_area = get_area_sum(polygons, [specified_vertices](const Polygon& poly)
                    {
                        return poly.points.size() == static_cast<std::size_t>(specified_vertices);
                    });
                }
            }
            catch (const std::invalid_argument&)
            {
                out << "<INVALID COMMAND>" << std::endl;
                return;
            }
        }
        out << std::fixed << std::setprecision(1) << total_area << std::endl;
    }

    void extreme_param(const std::vector<Polygon>& polygons, std::istream&, std::ostream& out, bool find_max, const std::string& type)
    {
        double result = -1.0;
        if (type == "AREA")
        {
            result = get_extreme_area(polygons, find_max);
        }
        else if (type == "VERTEXES")
        {
            int count = get_extreme_vertex_count(polygons, find_max);
            if (count != -1)
            {
                out << count << '\n';
                return;
            }
        }
        else
        {
            out << "<INVALID COMMAND>" << '\n';
            return;
        }

        if (result != -1.0)
        {
            out << std::fixed << std::setprecision(1) << result << '\n';
        }
        else
        {
            out << "<INVALID COMMAND>" << '\n';
        }
    }

    void count_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::string param;
        in >> param;

        if (param == "ODD")
        {
            out << get_count(polygons, [](const Polygon& poly) { return poly.points.size() % 2 != 0; }) << std::endl;
        }
        else if (param == "EVEN")
        {
            out << get_count(polygons, [](const Polygon& poly) { return poly.points.size() % 2 == 0; }) << std::endl;
        }
        else
        {
            try
            {
                int specified_vertices = std::stoi(param);
                if (specified_vertices < 3)
                {
                    out << "0" << std::endl;
                }
                else
                {
                    out << get_count(polygons, [specified_vertices](const Polygon& poly)
                    {
                        return poly.points.size() == static_cast<std::size_t>(specified_vertices);
                    }) << std::endl;
                }
            }
            catch (const std::invalid_argument&)
            {
                out << "<INVALID COMMAND>" << std::endl;
            }
        }
    }

    void rects_param(const std::vector<Polygon>& polygons, std::istream&, std::ostream& out)
    {
        out << count_rectangles(polygons) << '\n';
    }

    void maxseq_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        Polygon target;
        if (in >> target)
        {
            out << max_sequence(polygons, target) << '\n';
        }
        else
        {
            out << "<INVALID COMMAND>" << '\n';
        }
    }
}
