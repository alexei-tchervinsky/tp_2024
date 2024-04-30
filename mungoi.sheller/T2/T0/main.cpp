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