#include "datastruct.h"
#include "comparator.h"
#include <limits>

int main()
{
  std::vector<lst::Data> data;
  while (std::cin)
  {
    try
    {
      std::copy(
        std::istream_iterator<lst::Data>(std::cin),
        std::istream_iterator<lst::Data>(),
        std::back_inserter(data)
      );
    }
    catch (const lst::BadInput& err)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
  }
  std::stable_sort(data.begin(), data.end(), lst::DataComparator());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<lst::Data>(std::cout,"\n")
  );
  return 0;
}
