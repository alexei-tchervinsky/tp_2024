#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    using namespace Data;
    std::vector<DataStruct> data{std::istream_iterator<DataStruct>{std::cin}, {}};

    data.erase(std::remove_if(data.begin(), data.end(), [](const DataStruct &d) { return d.key3.empty(); }),
               data.end());

    if (!data.empty()) {
        std::sort(data.begin(), data.end());
        std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    }

    return 0;
}
