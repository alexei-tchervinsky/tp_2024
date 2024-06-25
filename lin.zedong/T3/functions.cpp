#include "functions.hpp"
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>

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
        auto& p = poly.points;

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

    double get_max_area(const std::vector<Polygon>& polygons)
    {
        if (polygons.empty())
        {
            return -1;
        }

        return std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
        {
            return a.calculate_area() < b.calculate_area();
        })->calculate_area();
    }

    double get_min_area(const std::vector<Polygon>& polygons)
    {
        if (polygons.empty())
        {
            return -1;
        }
        return std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
        {
            return a.calculate_area() < b.calculate_area();
        })->calculate_area();
    }

    int get_count(const std::vector<Polygon>& polygons, std::function<bool(const Polygon&)> pred)
    {
        return std::count_if(polygons.begin(), polygons.end(), pred);
    }

    int get_max_vertexes(const std::vector<Polygon>& polygons)
    {
        if (polygons.empty())
        {
            return -1;
        }
        return std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
        {
            return a.points.size() < b.points.size();
        })->points.size();
    }

    int get_min_vertexes(const std::vector<Polygon>& polygons)
    {
        if (polygons.empty())
        {
            return -1;
        }
        return std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
        {
            return a.points.size() < b.points.size();
        })->points.size();
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
        if (!(in >> param))
        {
            out << "<INVALID COMMAND>\n";
            return;
        }

        if (param == "EVEN")
        {
            out << std::fixed << std::setprecision(1) << get_area_sum(polygons, [](const Polygon& poly)
            {
                return poly.points.size() % 2 == 0;
            }) << '\n';
        }
        else if (param == "ODD")
        {
            out << std::fixed << std::setprecision(1) << get_area_sum(polygons, [](const Polygon& poly)
            {
                return poly.points.size() % 2 != 0;
            }) << '\n';
        }
        else if (param == "MEAN")
        {
            out << std::fixed << std::setprecision(1) << get_mean_area(polygons) << '\n';
        }
        else
        {
            std::size_t num_vertices;
            std::istringstream iss(param);
            if (iss >> num_vertices)
            {
                out << std::fixed << std::setprecision(1) << get_area_sum(polygons, [num_vertices](const Polygon& poly)
                {
                    return poly.points.size() == num_vertices;
                }) << '\n';
            }
            else
            {
                out << "<INVALID COMMAND>\n";
            }
        }
    }

    void max_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::string param;
        in >> param;
        if (param == "AREA")
        {
            out << std::fixed << std::setprecision(1) << get_max_area(polygons) << '\n';
        }
        else if (param == "VERTEXES")
        {
            out << get_max_vertexes(polygons) << '\n';
        }
        else
        {
            out << "<INVALID COMMAND>" << '\n';
        }
    }

    void min_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
    {
        std::string param;
        in >> param;
        if (param == "AREA")
        {
            out << std::fixed << std::setprecision(1) << get_min_area(polygons) << '\n';
        }
        else if (param == "VERTEXES")
        {
            out << get_min_vertexes(polygons) << '\n';
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
        if (param == "EVEN")
        {
            out << get_count(polygons, [](const Polygon& poly)
            {
                return poly.points.size() % 2 == 0;
            }) << '\n';
        }
        else if (param == "ODD")
        {
            out << get_count(polygons, [](const Polygon& poly)
            {
                return poly.points.size() % 2 != 0;
            }) << '\n';
        }
        else
        {
            try
            {
                std::size_t num_vertices = std::stoul(param);
                out << get_count(polygons, [num_vertices](const Polygon& poly)
                {
                    return poly.points.size() == num_vertices;
                }) << '\n';
            }
            catch (const std::invalid_argument&)
            {
                out << "<INVALID COMMAND>" << '\n';
            }
        }
    }

    int count_even_vertexes(const std::vector<Polygon>& polygons)
    {
        return std::count_if(polygons.begin(), polygons.end(), [](const Polygon& poly)
        {
            return poly.points.size() % 2 == 0;
        });
    }

    int count_odd_vertexes(const std::vector<Polygon>& polygons)
    {
        return std::count_if(polygons.begin(), polygons.end(), [](const Polygon& poly)
        {
            return poly.points.size() % 2 != 0;
        });
    }

    int count_specific_vertexes(const std::vector<Polygon>& polygons, int num)
    {
        return std::count_if(polygons.begin(), polygons.end(), [num](const Polygon& poly)
        {
            return poly.points.size() == static_cast<std::vector<geometry::Point>::size_type>(num);
        });
    }

    std::string generate_polygon_description(const Polygon& polygon)
    {
        std::stringstream ss;
        ss << polygon.points.size() << " ";

        for (const Point& point : polygon.points)
        {
            ss << "(" << point.x << ";" << point.y << ") ";
        }

        return ss.str();
    }

    int max_sequence_of_polygon(const std::vector<Polygon>& polygons, const std::string& polygonDesc)
    {
        int maxSequence = 0;
        int currentSequence = 0;

        for (const Polygon& poly : polygons)
        {
            std::string desc = generate_polygon_description(poly);
            if (desc == polygonDesc)
            {
                currentSequence++;
                maxSequence = std::max(maxSequence, currentSequence);
            }
            else
            {
                currentSequence = 0;
            }
        }

        return maxSequence;
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
