#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

int main() {
    using namespace Data;
    std::vector<DataStruct> data;
    DataStruct temp;

    while (true) {
        if (std::cin >> temp) {
            if (!temp.key3.empty()) {
                data.push_back(temp);
            }
        } else {
            if (std::cin.eof()) break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if (!data.empty()) {
        std::sort(data.begin(), data.end());
        std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    }

    return 0;
}
