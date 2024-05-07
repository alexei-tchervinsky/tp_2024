#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include "mynspace.hpp"

int main()
{
  using nspace::Data;

  std::vector< Data > data;
  std::istringstream iss("{ \"key1\": 20D, \"key2\": 89l,\"key3\": \"Just started learning github\" }");

  std::copy(
    std::istream_iterator< Data >(iss),
    std::istream_iterator< Data >(),
    std::back_inserter(data)
  );
  //std::cout <<"line 90: "<< data[0].key1<<'\n';
  
  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< Data >(std::cout, "\n")
  );
  
  
  std::vector< Data > data2;
  std::istringstream iss2("{ \"key1\": 15D, \"key2\": 21l,\"key3\": \"Git Lab T2\" }");
  
  //std::cout <<"line 102: "<< data2[0]<<'\n';
  std::copy(
    std::istream_iterator< Data >(iss2),
    std::istream_iterator< Data >(),
    std::back_inserter(data2)
  );
  
  std::cout << "Data2:\n";
  
    std::copy(
    std::begin(data2),
    std::end(data2),
    std::ostream_iterator< Data >(std::cout, "\n")
  );
  
  std::vector< Data > data3;
  std::istringstream iss3("{ \"key1\": 3D, \"key2\": 34l,\"key3\": \"Git Lab T3\" }");
  
  std::copy(
    std::istream_iterator< Data >(iss3),
    std::istream_iterator< Data >(),
    std::back_inserter(data3)
  );
  
  std::cout << "Data3:\n";
  
    std::copy(
    std::begin(data3),
    std::end(data3),
    std::ostream_iterator< Data >(std::cout, "\n")
  );
  
  std::vector< Data > data4;
  std::istringstream iss4("{ \"key1\": 3D, \"key2\": 38l,\"key3\": \"Git Lab dublicate\" }");
  
  std::copy(
    std::istream_iterator< Data >(iss4),
    std::istream_iterator< Data >(),
    std::back_inserter(data4)
  );
  
  std::cout << "Data4:\n";
  
    std::copy(
    std::begin(data4),
    std::end(data4),
    std::ostream_iterator< Data >(std::cout, "\n")
  );

  std::cout << "sorting data items\n";
  std::vector< Data > DItems[4] = {data, data2, data3, data4};

  sort(DItems, 4);
  for(size_t i = 0; i < 4; ++i){
      std::copy(
      std::begin( DItems[i]),
      std::end( DItems[i]),
      std::ostream_iterator< Data >(std::cout, "\n")
      );
  }
  
  return 0;
}
