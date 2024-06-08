#include "data_struct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<namesp::DataStruct> dataStructs;

    std::copy(std::istream_iterator<namesp::DataStruct>(std::cin), std::istream_iterator<namesp::DataStruct>(), std::back_inserter(dataStructs));

    std::sort(dataStructs.begin(), dataStructs.end(), namesp::Compare());

    std::copy(dataStructs.begin(), dataStructs.end(), std::ostream_iterator<namesp::DataStruct>(std::cout, "\n"));

    return 0;
}