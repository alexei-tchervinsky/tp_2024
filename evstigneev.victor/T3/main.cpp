#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include "commands.hpp"
#include "dataStruct.hpp"
#include <iomanip>
#include <map>

int main(int argc, char* argv[])
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
    return 2;
  }

  std::cout << std::setprecision(1) << std::fixed;
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
  in.close();
  std::map<std::string,
    std::function<void(std::istream&, std::ostream&)>> cmd;
  cmd["AREA"] = std::bind(evstigneev::area, poly, std::placeholders::_1,
    std::placeholders::_2);
  cmd["MAX"] = std::bind(evstigneev::max, poly, std::placeholders::_1,
    std::placeholders::_2);
  cmd["MIN"] = std::bind(evstigneev::min, poly, std::placeholders::_1,
    std::placeholders::_2);
  cmd["COUNT"] = std::bind(evstigneev::count, poly, std::placeholders::_1,
    std::placeholders::_2);
  cmd["LESSAREA"] = std::bind(evstigneev::lessArea, poly, std::placeholders::_1,
    std::placeholders::_2);
  cmd["MAXSEQ"] = std::bind(evstigneev::mxSeq, poly, std::placeholders::_1,
    std::placeholders::_2);

  std::string comm;
  while (std::cin >> comm)
  {
    try
    {
      cmd.at(comm)(std::cin, std::cout);
    }
    /*catch (const std::logic_error&)
    {
      std::cerr << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }*/
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
