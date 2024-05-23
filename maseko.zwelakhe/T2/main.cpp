#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "nspace.hpp"



int main()
{
    using nspace::Data;

    std::vector< Data > data;
    std::istringstream iss("{ \"key1\": 20D, \"key2\": 89l,\"key3\": \"Just started learning github\" }");

    while (!std::cin.eof()) {
    std::copy(
        std::istream_iterator< Data >(std::cin),
        std::istream_iterator< Data >(),
        std::back_inserter(data)
    );
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    }
    
    std::sort(data.begin(), data.end(),
        [](const Data& a, const Data& b) {
            if (a.key1 != b.key1)
            {
                return (a.key1 < b.key1);
            }
            if (a.key2 != b.key2)
            {
                return (a.key2 < b.key2);
            }

            return (a.key3.length() < b.key3.length());
        });
        
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator< Data >(std::cout, "\n")
    );

    /*std::vector< Data > data2;
    std::istringstream iss2("{ \"key1\": 15D, \"key2\": 21l,\"key3\": \"Git Lab T2\" }");

    std::copy(
        std::istream_iterator< Data >(iss2),
        std::istream_iterator< Data >(),
        std::back_inserter(data2)
    );


    std::vector< Data > data3;
    std::istringstream iss3("{ \"key1\": 3D, \"key2\": 34l,\"key3\": \"Git Lab T3\" }");

    std::copy(
        std::istream_iterator< Data >(iss3),
        std::istream_iterator< Data >(),
        std::back_inserter(data3)
    );


    std::vector< Data > data4;
    std::istringstream iss4("{ \"key1\": 3D, \"key2\": 38l,\"key3\": \"Git Lab dublicate\" }");

    std::copy(
        std::istream_iterator< Data >(iss4),
        std::istream_iterator< Data >(),
        std::back_inserter(data4)
    );



    std::cout << "\nsorting data items\n";
    std::vector< Data > DItems[4] = { data, data2, data3, data4 };

    for (size_t i = 0; i < 4; ++i) {
        std::copy(
            std::begin(DItems[i]),
            std::end(DItems[i]),
            std::ostream_iterator< Data >(std::cout, "\n")
        );
    }
    std::cout << "\n";

    sort(DItems, 4);
    for (size_t i = 0; i < 4; ++i) {
        std::copy(
            std::begin(DItems[i]),
            std::end(DItems[i]),
            std::ostream_iterator< Data >(std::cout, "\n")
        );
    }*/

    return 0;
}


