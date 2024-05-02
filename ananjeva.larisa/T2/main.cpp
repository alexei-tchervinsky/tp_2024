#include <iostream>
#include "DataStruct.hpp"
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

int main() {
  std::vector<ananjeva::DataStruct> data;
  while(!std::cin.eof()) {
    std::copy(
      std::istream_iterator<ananjeva::DataStruct>(std::cin),
      std::istream_iterator<ananjeva::DataStruct>(),
      std::back_inserter(data)
    );
    if (std::cin.fail() && !std::cin.eof()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<ananjeva::DataStruct>(std::cout, "\n")
  );

  return 0;
}
