#include "Comparator.hpp"
#include "DataStruct.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include <bitset>
int main()
{
    using TAhm::DataItem;
    std::vector<DataItem> data;
    while (!std::cin.eof())
    {
        std::copy(std::istream_iterator<DataItem>{std::cin}, std::istream_iterator<DataItem>{}, std::back_inserter(data));
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::stable_sort(data.begin(), data.end(), TAhm::Comparator());
    std::copy(data.cbegin(), data.cend(), std::ostream_iterator<DataItem>(std::cout, "\n"));
    return 0;
}