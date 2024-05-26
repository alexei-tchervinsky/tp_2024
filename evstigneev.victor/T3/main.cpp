#include <fstream>
#include <iostream>
#include <functional>
#include <limits>
#include <map>
#include <iterator>
#include "commands.hpp"
#include <iomanip>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return -1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Error: unable to open the file\n";
    return -1;
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
  /*std::map<std::string,
    std::function<void(const std::vector<evstigneev::Polygon>&)>> cmd =
  {
    {"AREA", evstigneev::area},
    {"MAX", evstigneev::max},
    {"MIN", evstigneev::min},
    {"COUNT", evstigneev::count},
    {"LESSAREA", evstigneev::lessArea}
  };*/
  /*std::string command = "";
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
  }*/
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::string cmd;
    std::cin >> cmd;
    try
    {
      //cmd.at(command)(poly);
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
      else if (cmd == "LESSAREA")
      {
        evstigneev::lessArea(poly);
      }
      else if (cmd == "MAXSEQ")
      {
        evstigneev::mxSeq(poly);
      }
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
