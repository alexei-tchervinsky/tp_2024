#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "Polygon.hpp"
#include <limits>

using namespace semzin;
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong input\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  std::vector<Polygon> polygons;
  while (!input.eof())
  {
    std::copy(
        std::istream_iterator<Polygon>{input},
        std::istream_iterator<Polygon>{},
        std::back_inserter(polygons));
    if(input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
