#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data_struct.h"

int main()
{
    std::vector<DataStruct> data;

    bool foundValidRecord = false;

    // Some examples to test the code
    /* ( :key1 45.0d :key2 123ll :key3 "Apple" )
       ( :key1 10.5d :key2 -45ll :key3 "Banana" )
       ( :key1 45.0d :key2 123ll :key3 "Cherry" )
       ( :key1 10.5d :key2 123ll :key3 "Date" )
       ( :key1 45.0d :key2 -123ll :key3 "Fig" ) */

    std::cout << "sheller_valmiro_mungoi" << std::endl;
    std::cout << "Enter data (terminate input with an empty line):" << std::endl;
    std::cout << "Rellehs_mung:" << std::endl;

    std::string line;
    while (std::getline(std::cin, line) && !line.empty())
    {
        std::istringstream iss(line);
        DataStruct ds;
        if (iss >> ds)
        {
            data.push_back(ds);
            foundValidRecord = true;
        }
        else
        {
            std::cerr << "Invalid input format, skipping line_Rellehs: " << line << std::endl;
        }
    }

    if (!foundValidRecord)
    {
        std::cerr << "Cannot determine input. Test skipped_Rellehs" << std::endl;
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
