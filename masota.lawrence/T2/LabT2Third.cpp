// LabT2Third.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "DataStruct.h"

using namespace lawrenced;

int main() {
    std::vector<DataStruct> data;
    DataStruct temp;
    while (std::cin >> temp) {
        data.push_back(temp);
    }

    std::sort(data.begin(), data.end());

    for (const auto& d : data) {
        std::cout << d << std::endl;
    }

    return 0;
}



