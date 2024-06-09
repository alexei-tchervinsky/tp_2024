#include "data_struct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <limits>

int main()
{
    std::vector<namesp::DataStruct> dataStructs;
    while (std::cin.eof() != true)
    {
        std::copy(
            std::istream_iterator<namesp::DataStruct>{std::cin},
            std::istream_iterator<namesp::DataStruct>{},
            std::back_inserter(dataStructs));
        if (std::cin.fail() == true)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(
        dataStructs.begin(),
        dataStructs.end()
    );

    std::copy(
        dataStructs.begin(),
        dataStructs.end(),
        std::ostream_iterator<namesp::DataStruct>{std::cout, "\n"}
    );

    return 0;
}
