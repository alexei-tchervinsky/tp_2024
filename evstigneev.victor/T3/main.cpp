#include <fstream>
#include <iostream>
#include <functional>
#include <limits>
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
    if (in.fail() && !in.eof())
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::map<std::string, std::function<void (const std::vector<evstigneev::Polygon>&)>> cmd;
  {
    cmd["AREA"] = evstigneev::area;
    cmd["MAX"] = evstigneev::max;
    cmd["MIN"] = evstigneev::min;
    cmd["COUNT"] = evstigneev::count;
  }
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmd.at(command)(poly);
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    catch (const std::logic_error&)
    {
      std::cerr << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
