#include "datastruct.h"
#include "comparator.h"
int main()
{
  std::vector<lst::Data> data;
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
    std::cerr << err.what() << "\n";
  }
  std::stable_sort(data.begin(), data.end(), lst::DataComparator());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<lst::Data>(std::cout,"\n")
  );
  return 0;
}
