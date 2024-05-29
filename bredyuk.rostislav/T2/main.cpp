#include "DataStruct.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

int main() {
    std::vector<ds::DataStruct> data;
    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<ds::DataStruct>(std::cin),
            std::istream_iterator<ds::DataStruct>(),
            std::back_inserter(data)
        );
        if (std::cin.fail() && !std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::sort(data.begin(), data.end());
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<ds::DataStruct>{std::cout, "\n"}
    );
    return 0;
}