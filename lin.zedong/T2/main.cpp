#include "data_struct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace mungoi;

int main()
{
    std::vector<DataStruct> dataStructs;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(dataStructs));

    std::sort(dataStructs.begin(), dataStructs.end(), Compare());

    std::copy(dataStructs.begin(), dataStructs.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}