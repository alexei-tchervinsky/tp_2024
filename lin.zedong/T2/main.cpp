#include "data_struct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <limits>

int main()
{
    using namespace namesp;
    std::vector< DataStruct > data;
    DataStruct input;
    while (std::cin >> input)
    {
        data.push_back(input);
    }

    if (std::cin.fail() && !std::cin.eof())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::sort(data.begin(), data.end());

    for (const auto& elem : data)
    {
        std::cout << elem << '\n';
    }

    return 0;
}
