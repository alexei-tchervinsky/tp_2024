#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Polygon.hpp"
#include <iostream>
#include <vector>

void less_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out);
void same_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out);
void area_command(const std::vector<kabalin::Polygon> &polygons,
                  std::istream &in, std::ostream &out);
void max_command(const std::vector<kabalin::Polygon> &polygons,
                 std::istream &in, std::ostream &out);
void min_command(const std::vector<kabalin::Polygon> &polygons,
                 std::istream &in, std::ostream &out);
void count_command(const std::vector<kabalin::Polygon> &polygons,
                   std::istream &in, std::ostream &out);
void ioUI(const std::vector<kabalin::Polygon> &polygons, std::istream &in,
          std::ostream &out);

#endif // COMMANDS_HPP
