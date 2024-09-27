#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "struct.hpp"

int main()
{
    using nspace::Data;
    std::vector<Data> data;

    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<Data>(std::cin),
            std::istream_iterator<Data>(),
            std::back_inserter(data)
        );

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(data.begin(), data.end(),
        [](const Data& a, const Data& b) {
            if (a.key1 != b.key1) {
                return a.key1 < b.key1;
            }
            if (a.key2 != b.key2) {
                return a.key2 < b.key2;
            }
            return a.key3.length() < b.key3.length();
        });

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<Data>(std::cout, "\n")
    );

    return 0;
}