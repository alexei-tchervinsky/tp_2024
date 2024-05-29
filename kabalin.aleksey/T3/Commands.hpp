#ifndef COMANDS_HPP
#define COMANDS_HPP
#include "Structs.hpp"
#include <algorithm>
#include <functional>
#include <regex>

const std::string ERROR_OF_COMMAND = "<INVALID COMMAND>";

int isIntOrDigit(std::string str);
void area(std::vector<kabalin::Polygon> &data, std::string &str);
void max(std::vector<kabalin::Polygon> &data, std::string &str);
void min(std::vector<kabalin::Polygon> &data, std::string &str);
void count(std::vector<kabalin::Polygon> &data, std::string &str);
void maxSeq(std::vector<kabalin::Polygon> &data);
void lessArea(std::vector<kabalin::Polygon> &data);

#endif
