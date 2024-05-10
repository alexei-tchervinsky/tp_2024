#include "Struct.hpp"
#include "Commands.hpp"
#include <iterator>
#include <algorithm>
#include <limits>
#include <exception>
#include <map>
#include <functional>

using namespace ananev;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "FILENAME_NOT_SPECIFIED\n";
    return 1;
  }
  std::ifstream in;
  in.open(argv[1]);
  if (!in)
  {
    std::cerr << "FILE_NOT_FOUND\n";
    return 1;
  }
  std::vector< ananev::Polygon > polygons;
  while (!in.eof())
  {
    std::copy(std::istream_iterator< ananev::Polygon >(in),
    std::istream_iterator< ananev::Polygon >(),
    std::back_inserter(polygons));
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::map< std::string, std::function< void(const std::vector< ananev::Polygon >, std::istream &, std::ostream &) > > commands
  {
    {"AREA", ananev::area_param},
    {"MAX", ananev::max_param},
    {"MIN", ananev::min_param},
    {"COUNT", ananev::count_param},
  };

  while (!std::cin.eof())
  {
    std::string key;
    std::cin >> key;
    if (commands.find(key) != commands.end())
    {
      auto command = std::bind(commands[key], std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
      command(polygons, std::cin, std::cout);
    }
    else if (!std::cin.eof())
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
