#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iomanip>
#include "data_struct.h"

int main() {
    std::vector<DataStruct> data;

    std::string testData = R"(
    (:key1 45.0d:key2 123ll:key3 "Apple":)
    (:key1 10.5d:key2 -45ll:key3 "Banana":)
    (:key1 45.0d:key2 123ll:key3 "Cherry":)
    (:key1 10.5d:key2 123ll:key3 "Date":)
    (:key1 45.0d:key2 -123ll:key3 "Fig":)
    )";

    std::istringstream iss(testData);

    std::copy(std::istream_iterator<DataStruct>(iss),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));

    std::sort(data.begin(), data.end());

    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
