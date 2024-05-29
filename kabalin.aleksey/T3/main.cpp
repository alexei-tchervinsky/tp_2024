#include "Commands.hpp"
#include "Structs.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <limits>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Ircorrect filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argv[1];
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "File not found\n";
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;

  std::vector<kabalin::Polygon> data;

  while (!file.eof()) {
    std::copy(std::istream_iterator<kabalin::Polygon>(file),
              std::istream_iterator<kabalin::Polygon>(),
              std::back_inserter(data));

    if (!file.eof() && file.fail()) {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  try {
    std::string comand;
    while (true) {
      if (!(std::getline(std::cin, comand, '\n') && !comand.empty() &&
            !(std::cin.eof())))
        break;

      std::string cmd, parametr;
      std::istringstream in(comand);
      in >> cmd >> parametr;

      try {
        if (cmd == "AREA") {
          area(data, parametr);
        } else if (cmd == "MAX") {
          max(data, parametr);
        } else if (cmd == "MIN") {
          min(data, parametr);
        } else if (cmd == "COUNT") {
          count(data, parametr);
        } else if (cmd == "SAME") {
          std::istringstream str(parametr);
          maxSeq(data);
        } else if (cmd == "LESSAREA") {
          std::istringstream str(parametr);
          lessArea(data);
        } else if (cmd != "")
          throw ERROR_OF_COMMAND;
      } catch (std::string &error) {
        std::cout << error << std::endl;
      }
    }
    return EXIT_SUCCESS;
  } catch (...) {
    std::cout << "Something went wrong!" << std::endl;
    return EXIT_FAILURE;
  }
}
