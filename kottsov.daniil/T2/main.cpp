#include "datastruct.h"
#include "comparator.h"
int main()
{
  std::vector<lst::Data> data;
  std::copy(
    std::istream_iterator<lst::Data>(std::cin),
    std::istream_iterator<lst::Data>(),
    std::back_inserter(data)
  );
  std::stable_sort(data.begin(), data.end(), lst::DataComparator());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<lst::Data>(std::cout,"\n")
  );
  return 0;
}
