#include <algorithm>
#include <iterator>
#include <vector>
#include <limits>
#include "Struct.hpp"
#include "Compare.hpp"

int main()
{
  std::vector<ananev::DataStruct> data_struct;
  while (std::cin.eof() != true)
  {
    std::copy(std::istream_iterator<ananev::DataStruct>(std::cin),
    std::istream_iterator<ananev::DataStruct>(),
    std::back_inserter(data_struct));
    if (std::cin.fail() == true)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::sort(data_struct.begin(), data_struct.end(), ananev::Compare());
  std::copy(data_struct.cbegin(), data_struct.cend(), std::ostream_iterator<ananev::DataStruct>{std::cout, "\n"});
  return 0;
}