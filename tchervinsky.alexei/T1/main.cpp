#include "datastruct.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>

int main()
{
  std::vector< tchervinsky::DataStruct > data;
  do
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(
      std::istream_iterator< tchervinsky::DataStruct >(std::cin),
      std::istream_iterator< tchervinsky::DataStruct >(),
      std::back_inserter(data));
  } while (!std::cin.eof());

  std::sort(data.begin(), data.end());

  std::copy(data.begin(), data.end(), std::ostream_iterator< tchervinsky::DataStruct >(std::cout, "\n"));

  return 0;
}
