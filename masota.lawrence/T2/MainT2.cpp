#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "DataStruct.h"

using namespace jean;

int main() {
  std::ifstream file("input.txt");
  if (!file.is_open()) {
    std::cerr << "Failed to open input file." << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<DataStruct> data;
  DataStruct temp;
  char ch;
  while (file >> std::ws >> ch) {
    if (ch == '(') {  // Valid start of data structure
      file.putback(ch);  // Put the character back for correct parsing
      if (file >> temp) {
        data.push_back(temp);
      }
    }
    else {
      std::cerr << "Unexpected character found, skipping line: '" << ch << "'" << std::endl;
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Skip to the next line
    }
  }

  std::sort(data.begin(), data.end());

  for (const auto& item : data) {
    std::cout << item << std::endl;
  }

  return 0;
}
