#include "Compare.h"

int main()
{
  std::vector<grudov::Data> data;
  while (std::cin)
  {
    try
    {
      std::copy(std::istream_iterator<grudov::Data>(std::cin), std::istream_iterator<grudov::Data>(), std::back_inserter(data));
    }
    catch (grudov::WrongInput& err)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
  }
  std::stable_sort(data.begin(), data.end(), grudov::Compare());
  std::copy(std::begin(data), std::end(data), std::ostream_iterator<grudov::Data>(std::cout,"\n"));
  return 0;
}