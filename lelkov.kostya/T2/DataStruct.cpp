#include "DataStruct.hpp"

std::istream & lelkov::operator>>(std::istream &in, DataStruct &value)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  StreamGuard StreamGuard(in);
  std::string key = "";
  DataStruct input;
  in >> Del{'('} >> Del{':'};
  for(int i = 0; i < 3; i++)
  {
    in >> key;
    if(key == "key1")
    {
      in >> UllLit{input.key1} >> Del{':'};
    }
    else if(key == "key2")
    {
      in >> UllOct{input.key2} >> Del{':'};
    }
    else if(key == "key3")
    {
      in >> Str{input.key3} >> Del{':'};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> Del{')'};
  if(in)
  {
    value = input;
  }
  return in;
}

std::ostream & lelkov::operator<<(std::ostream & out, const DataStruct &value)
{
  std::ostream::sentry guard(out);
  if(!guard)
  {
    return out;
  }
  StreamGuard StreamGuard(out);
  out << "(";
  out << ":key1 "  << value.key1 << "ull";
  out << ":key2 0" << std::oct << value.key2;
  out << ":key3 " << "\"" << value.key3 << "\":)";
  return out;
}

bool lelkov::operator>(const DataStruct &left, const DataStruct &right)
{
  if(left.key1 != right.key1)
  {
    return left.key1 > right.key1;
  }
  else if (left.key2 != right.key2)
  {
    return left.key2 > right.key2;
  }
  else if (left.key3.length() != right.key3.length())
  {
    return left.key3.length() > right.key3.length();
  }
  else
  {
    return false;
  }
}
bool lelkov::operator<(const DataStruct &left, const DataStruct &right)
{
  return !(left > right);
}
