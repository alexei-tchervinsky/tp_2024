#include <fstream>
#include <iostream>
#include <functional>
#include <map>
#include <iterator>
#include "commands.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }
  std::vector<evstigneev::Polygon> poly;
  while (!in.eof())
  {
    std::copy(
      std::istream_iterator<evstigneev::Polygon>(in),
      std::istream_iterator<evstigneev::Polygon>(),
      std::back_inserter(poly)
    );
  }
  std::map<std::string, std::function<std::ostream& (std::istream&, std::ostream&,
    std::vector<evstigneev::Polygon>&)>> cmd;
  {
    cmd["AREA"] = std::bind(evstigneev::area, std::placeholders::_1,
      std::placeholders::_2, std::placeholders::_3);
    cmd["MAX"] = std::bind(evstigneev::max, std::placeholders::_1,
      std::placeholders::_2, std::placeholders::_3);
    cmd["MIN"] = std::bind(evstigneev::min, std::placeholders::_1,
      std::placeholders::_2, std::placeholders::_3);
    cmd["COUNT"] = std::bind(evstigneev::count, std::placeholders::_1,
      std::placeholders::_2, std::placeholders::_3);
  }
  std::string command = "";
  while (std::cin >> command)
  {
    cmd.at(command)(std::cin, std::cout, poly);
  }
  return 0;
}
