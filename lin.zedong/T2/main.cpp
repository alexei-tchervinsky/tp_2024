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
    std::vector<DataStruct> data;

    while (true)
    {
        DataStruct temp;
        if (std::cin >> temp)
        {
            data.push_back(temp);
        }
        else if (std::cin.eof())
        {
            break;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

     if (!data.empty())
    {
        std::sort(data.begin(), data.end());
        std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    }

    return 0;
}
