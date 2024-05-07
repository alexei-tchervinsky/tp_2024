#include "mynspace.hpp"

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
