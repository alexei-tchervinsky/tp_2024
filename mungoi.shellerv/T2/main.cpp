#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data_struct.h"

int main()
{
    std::vector<DataStruct> data;
    std::istringstream iss(
        "( :key1 45.0d :key2 123ll :key3 \"Apple\" )\n"
        "( :key1 10.5d :key2 -45ll :key3 \"Banana\" )\n"
        "( :key1 45.0d :key2 123ll :key3 \"Cherry\" )\n"
        "( :key1 10.5d :key2 123ll :key3 \"Date\" )\n"
        "( :key1 45.0d :key2 -123ll :key3 \"Fig\" )\n"
    );

    bool foundValidRecord = false;

    std::copy_if(
        std::istream_iterator<DataStruct>(iss),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data),
        [&foundValidRecord](const DataStruct&) {
            foundValidRecord = true;
            return true;
        }
    );

    if (!foundValidRecord)
    {
        std::cerr << "Cannot determine input. Test skipped" << std::endl;
        return 1;
    }

    std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1)
            return a.key1 < b.key1;
        if (a.key2 != b.key2)
            return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
    });

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
