#include <iostream>
#include <fstream>
#include <limits>
#include "Functions.h"
#include "Geometry.h"

int main(int argc, char **argv)
{
  using namespace ermilov;

  if (argc != 2) {
    std::cerr << "BAD PARAMETERS" << '\n';
    return -1;
  }
  std::string file = argv[1];
  std::ifstream input(file);
  Polygon polygon;
  std::vector<Polygon> polygons;

  if (!input.is_open())
  {
    std::cerr << "BAD FILE" << '\n';
    return -1;
  }

  while (!input.eof())
  {
    input >> polygon;
    if (!input.fail())
    {
      polygons.push_back(polygon);
    }
    else
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  try
  {
    while (!std::cin.eof())
    {
      chooseCommand(std::cin, std::cout, polygons);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
}
