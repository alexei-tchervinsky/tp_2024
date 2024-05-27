#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <map>
#include <limits>
#include <functional>
#include <iostream>

#include "geometry.h"
#include "io.h"
#include "commands.h"
using namespace std::placeholders;


int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: Expected 1 command-line argument, but got " << argc - 1 << ".\n";
    return EXIT_FAILURE;
  }

  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Error: file didn't open\n";
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;
  std::vector<berezneva::Polygon> vec;

  while (!file.eof())
  {
    std::copy(
      std::istream_iterator<berezneva::Polygon>(file),
      std::istream_iterator<berezneva::Polygon>(),
      std::back_inserter(vec)
    );
    if (!file.eof() && file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::map< std::string, std::function<std::ostream &(const std::vector<berezneva::Polygon> &)> > cmds
  {
    {"AREA", std::bind(berezneva::area, _1, std::ref(std::cin), std::ref(std::cout))},
    {"MIN", std::bind(berezneva::min, _1, std::ref(std::cin), std::ref(std::cout))},
    {"MAX", std::bind(berezneva::max, _1, std::ref(std::cin), std::ref(std::cout))},
    {"COUNT", std::bind(berezneva::count, _1, std::ref(std::cin), std::ref(std::cout))},
    {"LESSAREA", std::bind(berezneva::lessArea, _1, std::ref(std::cin), std::ref(std::cout))},
    {"INTERSECTIONS", std::bind(berezneva::intersect, _1, std::ref(std::cin), std::ref(std::cout))}
  };

  std::string command;

  while (std::cin >> command)
  {
    try
    {
      if (std::cin.eof())
      {
        break;
      }
      cmds.at(command)(vec);
    }
    catch (std::exception& ex)
    {
      std::cout << ex.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
  }
}
