#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h"
#include "iofmtguard.h"

int main()
{
  using namespace ermilov;

  std::vector<DataStruct> vector;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator<DataStruct>{std::cin},
      std::istream_iterator<DataStruct>{},
      std::back_inserter(vector)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(vector.begin(), vector.end());
  std::copy(
    std::begin(vector),
    std::end(vector),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );

  return 0;
}
