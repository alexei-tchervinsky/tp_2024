#include "data_struct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <limits>

int main()
{
    try
    {
        std::istream_iterator<namesp::DataStruct> start(std::cin), end;
        if (start == end)
        {
            std::cerr << "Looks like there is no supported record. Cannot determine input. Test skipped" << std::endl;
            return 1;
        }
        std::vector<namesp::DataStruct> data(start, end);
        std::sort(data.begin(), data.end());
        std::copy(data.begin(), data.end(), std::ostream_iterator<namesp::DataStruct>(std::cout, "\n"));
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }
    return 0;
}
