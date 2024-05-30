#include "operations.h"
#include "polygon.h"
#include <fstream>
#include <sstream>
using namespace poly;

int main(int args, char* fileinput[])
{
  using inputType = Polygon;
  if (args!=2)
  {
    std::cerr << "invalid arguments\n";
    return 1;
  }
  std::ifstream input(fileinput[1]);
  if (!input)
  {
    std::cerr << "ifstream failure\n";
    return 1;
  }
  std::vector<inputType> vector;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator<inputType>(input),
      std::istream_iterator<inputType>(),
      std::back_inserter(vector)
    );
    if (!input && !input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
  }
  while (!std::cin.eof())
  {
    try
    {
      ioUI(vector,std::cin,std::cout);
    }
    catch (const std::logic_error& ex)
    {
      if (std::string(ex.what())==std::string("istream failure"))
      {
        return 0;
      }
      else if (std::string(ex.what())==std::string("invalid cmd"))
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
  }
  return 0;
}
