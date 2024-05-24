#include <iterator>
#include <iomanip>
#include <fstream>
#include <limits>

#include "command.hpp"

using namespace kladkovoj;

int main(int argC, char *argV[])
{
  if (argC != 2)
  {
    std::cerr << "INCORRECT USAGE" << std::endl;
    return 0;
  }

  std::string fileName = argV[1];

  std::ifstream file(fileName);

  if (!file)
  {
    std::cerr << "File not found!" << std::endl;
    return 0;
  }

  std::cout << std::setprecision(1) << std::fixed;
  std::vector<Polygon> data;
  while (!file.eof())
  {
    std::copy(std::istream_iterator<Polygon>(file), std::istream_iterator<Polygon>(), std::back_inserter(data));
    if (!file.eof()&& file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  try
  {
    while (!std::cin.eof())
    {
      std::string cmd;

      std::cin >> cmd;

      try
      {
        if (cmd == "AREA")
          command::area(data);
        else if (cmd == "MIN")
          command::min(data);
        else if (cmd == "MAX")
          command::max(data);
        else if (cmd == "COUNT")
          command::count(data);
        else if (cmd == "RECTS")
          command::rects(data);
        else if (cmd == "INTERSECTIONS")
          command::intersections(data);
        else if (!cmd.empty())
          throw "<INVALID COMMAND>";
      }
      catch (const char* err)
      {
        std::cout << err << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }

    return 0;
  }
  catch (...)
  {
    std::cerr << "Did I write this?..." << std::endl;
    return 0;
  }
}
