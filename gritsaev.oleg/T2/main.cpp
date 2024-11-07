#include <algorithm>
#include <iterator>
#include <vector>
#include <limits>
#include "Struct.hpp"
#include "Compare.hpp"

int main()
{
    std::vector<gritsaev::DataStruct> data_struct;
    while (std::cin.eof() != true)
    {
        std::copy(std::istream_iterator<gritsaev::DataStruct>(std::cin),
            std::istream_iterator<gritsaev::DataStruct>(),
            std::back_inserter(data_struct));
        if (std::cin.fail() == true)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::stable_sort(data_struct.begin(), data_struct.end(), gritsaev::Compare());
    std::copy(data_struct.cbegin(), data_struct.cend(), std::ostream_iterator<gritsaev::DataStruct>{std::cout, "\n"});
    return 0;
}
