#include <iostream>
#include <vector>
#include <algorithm>
#include "data_struct.h"

int main() {
    std::vector<DataStruct> dataVector;

    std::string line;
    while (std::getline(std::cin, line)) {
        try {
            DataStruct data;
            std::istringstream iss(line);
            iss >> data;
            dataVector.push_back(data);
        }
        catch (...) {
            continue;
        }
    }
    std::sort(dataVector.begin(), dataVector.end());

    for (const auto& data : dataVector) {
        std::cout << data << std::endl;
    }

    return 0;
}


//Doing the test
//(:key1 10.5d : key2 20ll : key3 "Hello" : )
//(:key1 5.0d : key2 15ll : key3 "World" : )
//(:key1 8.75d : key2 10ll : key3 "This is a test" : )#include <iostream>
