#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <limits>
#include "data_struct.h"
#include "compare.h"

int main()
{
    std::vector<mungoi::DataStruct> data_struct = {
        {45.0, 123, "Apple"},
        {10.5, -45, "Banana"},
        {45.0, 123, "Cherry"},
        {10.5, 123, "Date"},
        {45.0, -123, "Fig"}
    };

    std::stable_sort(data_struct.begin(), data_struct.end(), mungoi::Compare());
    std::copy(data_struct.cbegin(), data_struct.cend(), std::ostream_iterator<mungoi::DataStruct>{std::cout, "\n"});

    return 0;
}
