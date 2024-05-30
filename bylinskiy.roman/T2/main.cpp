#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "dataStruct.h"
#include "inOutPut.h"

int main()
{
    using namespace bylinskiy;
    using iit = std::istream_iterator< DataStruct >;
    using oit = std::ostream_iterator< DataStruct >;

    std::vector< DataStruct > dataStruct;

    while (std::cin.good()) {
        std::copy(iit(std::cin), iit(), std::back_inserter(dataStruct));
        if (std::cin.fail() && !std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore();
        }
    }

    std::sort(dataStruct.begin(), dataStruct.end());

    std::copy(std::begin(dataStruct), std::end(dataStruct), oit(std::cout, "\n"));
    return 0;
}
