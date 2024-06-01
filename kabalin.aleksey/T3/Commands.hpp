#include "polygon.hpp"
namespace kabalin {
void area_command(const std::vector<kabalin::Polygon> &polygons,
                  std::istream &in, std::ostream &out);
void max_command(const std::vector<kabalin::Polygon> &polygons,
                 std::istream &in, std::ostream &out);
bool arePolygonsCompatible(const kabalin::Polygon &a,
                           const kabalin::Polygon &b);
void less_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out);
void min_command(const std::vector<kabalin::Polygon> &polygons,
                 std::istream &in, std::ostream &out);
void count_command(const std::vector<kabalin::Polygon> &polygons,
                   std::istream &in, std::ostream &out);
void same_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out);
} // namespace kabalin
