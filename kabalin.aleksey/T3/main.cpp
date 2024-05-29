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
      argv[1]); // Убедимся, что файл успешно открыт перед его использованием
  if (!input) {
    std::cerr << "Failed to open input file\n";
    return 1;
  }
  std::vector<inputType> vector;
  while (input) { // Проверим наличие ошибок при чтении из файла перед
                  // использованием данных
    inputType polygon;
    if (input >> polygon) {
      vector.push_back(polygon);
    } else {
      break;
    }
  }
  while (!std::cin.eof()) {
    try {
      ioUI(vector, std::cin, std::cout);
    } catch (const std::logic_error &ex) {
      if (std::string(ex.what()) == std::string("istream failure")) {
        return 0;
      } else {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
