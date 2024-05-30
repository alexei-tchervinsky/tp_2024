#include "GraphRGR.h"
#include "inputUIRGR.h"

using namespace rgr;

int main()
{
  using NodeType = char;
  std::cout << "Selected Node type = char\n";
  std::cout << "Selected Weight type = default(int)\n";
  std::cout << "Enter a command, for the list of available commands type \"HELP\"\n";
  std::istream::sentry ward(std::cin);
  if (!ward)
  {
    std::cerr << "Nothing was allocated\n";
    return 0;
  }
  Graph<NodeType> graph;
  bool isFailstate = false;
  while (!std::cin.eof())
  {
    isFailstate = inputUI<NodeType>(graph,std::cout, std::cin);
    if (isFailstate)
    {
      return 0;
    }
    else
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
