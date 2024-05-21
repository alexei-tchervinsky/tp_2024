#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <limits>
#include "data_struct.h"
#include "compare.h"

int main()
{
    std::vector<mungoi::DataStruct> data_struct;
    while (std::cin.eof() != true)
    {
        std::copy(std::istream_iterator<mungoi::DataStruct>(std::cin),
            std::istream_iterator<mungoi::DataStruct>(),
            std::back_inserter(data_struct));
        if (std::cin.fail() == true)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::stable_sort(data_struct.begin(), data_struct.end(), mungoi::Compare());
    std::copy(data_struct.cbegin(), data_struct.cend(), std::ostream_iterator<mungoi::DataStruct>{std::cout, "\n"});
    return 0;
}
