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
  cmd["AREA"] = std::bind(evstigneev::area, std::placeholders::_1,
    std::cin, std::cout);
  cmd["MAX"] = std::bind(evstigneev::max, std::placeholders::_1,
    std::cin, std::cout);
  cmd["MIN"] = std::bind(evstigneev::min, std::placeholders::_1,
    std::cin, std::cout);
  cmd["COUNT"] = std::bind(evstigneev::count, std::placeholders::_1,
    std::cin, std::cout);
  cmd["LESSAREA"] = std::bind(evstigneev::lessArea, std::placeholders::_1,
    std::cin, std::cout);
  cmd["MAXSEQ"] = std::bind(evstigneev::mxSeq, std::placeholders::_1,
    std::cin, std::cout);

  std::string comm;
  while (std::cin >> comm)
  {
    try
    {
      cmd.at(comm)(poly);
    }
    catch (const std::logic_error&)
    {
      std::cerr << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
