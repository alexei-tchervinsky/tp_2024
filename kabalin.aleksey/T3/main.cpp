#include "Commands.hpp"
#include "Polygon.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  using inputType = kabalin::Polygon;
  if (argc != 2) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  std::ifstream input(
      argv[1]); // Ensure the file is successfully opened before using it
  if (!input) {
    std::cerr << "Failed to open input file\n";
    return 1;
  }
  std::vector<inputType> vector;
  while (input) { // Check for errors while reading from the file before using
                  // the data
    inputType polygon;
    try {
      if (input >> polygon) {
        vector.push_back(polygon);
      } else {
        break;
      }
    } catch (const std::invalid_argument &ex) {
      // Ignore invalid input lines and continue reading
    }
  }
  while (!std::cin.eof()) {
    try {
      ioUI(vector, std::cin, std::cout);
    } catch (const std::logic_error &ex) {
      if (std::string(ex.what()) == std::string("istream failure")) {
        return 0;
      } else if (std::string(ex.what()) == std::string("invalid cmd")) {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
