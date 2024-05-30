#include "Commands.h"

using namespace std::placeholders;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "file name not included\n";
    return 1;
  }
  std::ifstream in;
  in.open(argv[1]);
  if (!in)
  {
    std::cerr << "file nor found\n";
    return 1;
  }
  std::vector< grudov::Polygon > polygons;
  while (!in.eof())
  {
    std::copy(std::istream_iterator< grudov::Polygon >(in),
    std::istream_iterator< grudov::Polygon >(),
    std::back_inserter(polygons));
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::map< std::string, std::function< void(const std::vector< grudov::Polygon >, std::istream &, std::ostream &) > > commands
  {
    {"AREA", grudov::area},
    {"MAX", grudov::max},
    {"MIN", grudov::min},
    {"COUNT", grudov::count},
    {"RECTS", grudov::rects},
    {"MAXSEQ", grudov::maxseq}
  };

  std::cout << std::fixed;
  while (!std::cin.eof())
  {
    try
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
        throw std::invalid_argument("<INVALID COMMAND>");
      }
        }
    catch (const std::exception& ex)
    {
      std::cout << ex.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
