#include "Comparing.hpp"
#include "DataStruct.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <limits>

int main() {
    using AliKN::DataItem;
    std::vector<DataItem> records;

    while (!std::cin.eof()) {
        std::copy(std::istream_iterator<DataItem>{std::cin}, std::istream_iterator<DataItem>{}, std::back_inserter(records));

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::stable_sort(records.begin(), records.end(), AliKN::Comparing());
    std::copy(records.cbegin(), records.cend(), std::ostream_iterator<DataItem>(std::cout, "\n"));

    return 0;
}
