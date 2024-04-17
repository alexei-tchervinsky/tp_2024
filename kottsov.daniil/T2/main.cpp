#include "datastruct.h"
#include "comparator.h"
int main()
{
  std::vector<lst::Data> data;
  std::string inputLine;
  bool flag = true;
  while(flag)
  {
    flag = false;
    std::getline(std::cin, inputLine);
    std::istringstream iss(inputLine);
    try
    {
      std::copy(
        std::istream_iterator<lst::Data>(iss),
        std::istream_iterator<lst::Data>(),
        std::back_inserter(data)
      );
    }
    catch (const lst::BadInput& err)
    {
      std::cerr << err.what() << "\n";
      flag = true;
    }
  }
  std::stable_sort(data.begin(), data.end(), lst::DataComparator());
  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<lst::Data>(std::cout,"\n")
  );
  return 0;
}
