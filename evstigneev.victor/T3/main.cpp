#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "commands.hpp"
#include "dataStruct.hpp"
#include <iomanip>

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
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      if (cmd == "AREA")
      {
        evstigneev::area(poly);
      }
      else if (cmd == "MAX")
      {
        evstigneev::max(poly);
      }
      else if (cmd == "MIN")
      {
        evstigneev::min(poly);
      }
      else if (cmd == "COUNT")
      {
        evstigneev::count(poly);
      }
      else if (cmd == "LESSAREA")
      {
        evstigneev::lessArea(poly);
      }
      else if (cmd == "MAXSEQ")
      {
        evstigneev::mxSeq(poly);
      }
      else if (!std::cin)
      {
        throw std::runtime_error("<INVALID COMMAND>");
      }
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
