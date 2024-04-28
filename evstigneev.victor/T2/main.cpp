#include "datastruct.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>

int main()
{
  using namespace evstigneev;
  std::vector< DataStruct > data;
  DataStruct temp;
  while (std::cin >> temp)
  {
    data.push_back(temp);
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::cout << "Data:\n";
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
