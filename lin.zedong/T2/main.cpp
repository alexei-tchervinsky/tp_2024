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
    /*
    using namespace namesp;
    std::vector< DataStruct > data;
    while (!std::cin.eof())
    {
        std::copy(std::istream_iterator< DataStruct >{std::cin}, std::istream_iterator< DataStruct >{}, std::back_inserter(data));
        if (std::cin.fail())
        {
            std::cerr << "Looks like there is no supported record. Cannot determine input. Test skipped\n"; //
            std::cin.clear();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }
    std::sort(data.begin(), data.end());
    std::copy(std::begin(data), std::end(data), std::ostream_iterator< DataStruct >(std::cout, "\n"));

    return 0;
    */
}
