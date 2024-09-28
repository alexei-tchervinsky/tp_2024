#include "data_struct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

int main()
{
    using namespace namesp;
    std::vector<DataStruct> data;

    while (!std::cin.eof())
    {
        std::copy(std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data));

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if (!data.empty())
    {
        std::stable_sort(data.begin(), data.end(), Compare());
        std::copy(data.cbegin(), data.cend(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    }

    return 0;
}
