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


namespace nspace
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    // все перегрузки операторов ввода/вывода должны начинаться с проверки экземпляра класса sentry
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    // std::cout << "line 109: dest(DelimiterIO).exp: "<< dest.exp<<'\n';
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DoubleIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{ 'D' };
  }
  
  std::istream &operator>>(std::istream &in, LongLIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{ 'l' };
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    //std::cout << "line 143: dest(StringIO).ref: "<<dest.ref<<'\n';
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    //std::cout << "line 153: dest(LabelIO).exp: "<<dest.exp<<'\n';
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, Data &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Data input;
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using dbl = DoubleIO;
      using ll = LongLIO;
      using str = StringIO;
      in >> sep{ '{' };
      in >> label{ "key1" } >> sep{ ':' } >> dbl{ input.key1 };
      in >> sep{ ',' };
      in >> label{ "key2" } >> sep{ ':' } >> ll{ input.key2 };
      in >> sep{ ',' };
      in >> label{ "key3" } >> sep{ ':' } >> str{ input.key3 };
      in >> sep{ '}' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const Data &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 " << std::fixed << std::setprecision(1) << src.key1 << "d";
    out << ":key2 "<< std::fixed << std::setprecision(1) << src.key2 << "ll";
    out << ":key3 " << "\""<<src.key3<<"\"";
    out << ":)";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char > &s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
  
  
  bool sorted(std::vector< nspace::Data > Items[], size_t size){
    bool isOrdered = true;
    for(size_t i = 0; i < size-1; ++i){
        auto b = Items[i].begin();
        if(b->key1 > Items[i + 1].begin()->key1) isOrdered = false;
        else if(b->key2 > Items[i + 1].begin()->key2 && b->key1 == Items[i + 1].begin()->key1) isOrdered = false;
        else if(b->key3.length() > Items[i + 1].begin()->key3.length() && b->key2 == Items[i + 1].begin()->key2) isOrdered = false;
    }
    return isOrdered;
}
  void sort(std::vector< nspace::Data > Items[], size_t size){
    for(size_t i = 0; i < size; ++i){
      if(i == size-1){
        if(sorted(Items,size) == true) break;
        else{
          i = 0;
        }
      }
        
      auto b = Items[i].begin();
      auto nextItem = Items[i+1].begin();
      while(b != Items[i].end()){
      //std::cout << b->key1 << ',';
        if(b->key1 > nextItem->key1){
          std::vector< nspace::Data > temp = Items[i];
          Items[i] = Items[i+1];
          Items[i+1] = temp;
        }
        else if(b->key2 > nextItem->key2 && b->key1 == nextItem->key1){
          std::vector< nspace::Data > temp = Items[i];
          Items[i] = Items[i+1];
          Items[i+1] = temp;
        }
        else if(b->key3.length() > nextItem->key3.length() && b->key2 == nextItem->key2){
          std::vector< nspace::Data > temp = Items[i];
          Items[i] = Items[i+1];
          Items[i+1] = temp;
        }
        ++b;
      }
      std::cout << '\n';
    }
  }
}
