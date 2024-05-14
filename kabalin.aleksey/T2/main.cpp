#include "Compare.hpp"
#include "DataStruct.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

int main() {
  std::vector<kabalin::DataStruct> data_struct;
  while (std::cin.eof() != true)
  {
    std::copy(std::istream_iterator<kabalin::DataStruct>(std::cin),
    std::istream_iterator<kabalin::DataStruct>(),
    std::back_inserter(data_struct));
    if (std::cin.fail() == true)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::stable_sort(data_struct.begin(), data_struct.end(), kabalin::Compare());
  std::copy(data_struct.cbegin(), data_struct.cend(),std::ostream_iterator<kabalin::DataStruct>{std::cout, "\n"});
  return 0;
}