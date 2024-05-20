#include <fstream>
#include <iostream>
#include <functional>
#include <limits>
#include <map>
#include <iterator>
#include <iomanip>
#include <vector>
#include "commands.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Error: unable to open the file\n";
    return 1;
  }
  std::vector<evstigneev::Polygon> poly;
  while (!in.eof())
  {
    std::copy(
      std::istream_iterator<evstigneev::Polygon>(in),
      std::istream_iterator<evstigneev::Polygon>(),
      std::back_inserter(poly)
    );
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  using CMD = std::map<std::string, std::function<std::ostream& (std::istream&, std::ostream&,
    std::vector<evstigneev::Polygon>&)>>;
  CMD cmd;
  cmd["AREA"] = std::bind(evstigneev::area, std::placeholders::_1,
    std::placeholders::_2, std::placeholders::_3);
  cmd["MAX"] = std::bind(evstigneev::max, std::placeholders::_1,
    std::placeholders::_2, std::placeholders::_3);
  cmd["MIN"] = std::bind(evstigneev::min, std::placeholders::_1,
    std::placeholders::_2, std::placeholders::_3);
  cmd["COUNT"] = std::bind(evstigneev::count, std::placeholders::_1,
    std::placeholders::_2, std::placeholders::_3);
  cmd["LESSAREA"] = std::bind(evstigneev::lessArea, std::placeholders::_1,
    std::placeholders::_2, std::placeholders::_3);
  cmd["MAXSEQ"] = std::bind(evstigneev::maxSeq, std::placeholders::_1,
    std::placeholders::_2, std::placeholders::_3);

  std::string command = "";
  std::cout << std::setprecision(1) << std::fixed;
  while (std::cin >> command)
  {
    if (std::cin.eof())
    {
      return 0;
    }
    try
    {
      cmd.at(command)(std::cin, std::cout, poly);
      std::cout << "\n";
    }
    catch (const std::exception&)
    {
      std::cerr << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
