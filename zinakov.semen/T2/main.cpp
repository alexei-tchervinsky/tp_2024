#include "Comparator.hpp"
#include "DataStruct.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

int main()
{
  using semzin::Data;

  std::vector<Data> data;
  while (!std::cin.eof())
  {
    std::copy(std::istream_iterator<Data>{std::cin}, std::istream_iterator<Data>{}, std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::stable_sort(data.begin(), data.end(), semzin::Comparator());
  std::copy(data.cbegin(), data.cend(), std::ostream_iterator<Data>(std::cout, "\n"));
  return 0;
}
