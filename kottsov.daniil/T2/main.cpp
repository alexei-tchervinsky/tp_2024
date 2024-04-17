#include "datastruct.h"

int main() {
  std::vector<lst::Data> data;
  std::string inputLine;
  std::getline(std::cin, inputLine);
  while (inputLine!="0" && inputLine!="stop")
  {
    std::istringstream iss(inputLine);
    try {
      std::copy(
        std::istream_iterator<lst::Data>(iss),
        std::istream_iterator<lst::Data>(),
        std::back_inserter(data)
      );
    } 
    catch (const lst::BadInput& err) {
      std::cerr << err.what() << "\n";
      return 1;
    }
    std::getline(std::cin,inputLine);
  }
  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<lst::Data>(std::cout,"\n")
  );
  return 0;
}
