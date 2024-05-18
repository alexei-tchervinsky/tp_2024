#include "Commands.hpp"

namespace commands
{
  std::map< std::string, std::set<std::string> > input(std::istream &in)
  {
    std::vector< DictIO > dict;
    while (!in.eof())
    {
      std::copy(std::istream_iterator< DictIO >(in),
      std::istream_iterator< DictIO >(),
      std::back_inserter(dict));
      if (in.fail())
      {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    std::map< std::string, std::set<std::string> > input_dict;
    for (auto& el : dict)
    {
      input_dict[el.dict_el.first] = el.dict_el.second;
    }
    return input_dict;
  }
  void OPEN(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
  std::istream &in, std::ostream &out)
  {
    if (dict->first != "")
    {
      throw std::invalid_argument("<OLD DICT IS OPENED>");
    }
    if (in.get() == '\n')
    {
      throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
    }
    std::string input_name;
    in >> input_name;
    std::ifstream input_file(input_name);
    if (!input_file)
    {
      throw std::invalid_argument("<CANT FIND FILE>");
    }
    if (in.get() != '\n')
    {
      throw std::invalid_argument("<EXCESS ARGUMENT>");
    }
    dict->first = input_name;
    dict->second = input(input_file);
    out << "#succeed#\n";
  }

  void CLOSE(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
  std::istream &in, std::ostream &out)
  {
    std::string save = "N";
    if (in.get() != '\n')
    {
      in >> save;
      if (in.get() != '\n')
    {
      throw std::invalid_argument("<EXCESS ARGUMENT>");
    }
    }
    if (dict->first == "")
    {
      throw std::invalid_argument("<DICT ISNT OPEN>");
    }
    if (save == "SAVE")
    {
      std::ofstream output_file(dict->first);
      if (!output_file)
      {
        throw std::invalid_argument("<CANT FIND FILE>");
      }
      output_file.clear();
      for (auto pair = dict->second.begin(); pair != dict->second.end(); pair++)
      {
        output_file << "{" << pair->first << " -";
        for (auto trans = pair->second.begin(); trans != pair->second.end(); trans++)
        {
          output_file << " " << trans->data();
        }
        output_file << "}\n";
      }
      out << "#close " << dict->first << " and save#\n";
    }
    else if (save != "N")
    {
      throw std::invalid_argument("<EXCESS ARGUMENT>");
    }
    else
    {
      out << "#close " << dict->first << "#\n";
    }
    dict->first = "";
    dict->second.clear();
  }
  void COMPARE(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
  void MERGE(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dicts,
  std::istream &in, std::ostream &out){}

  void INSERT(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
  std::istream &in, std::ostream &out)
  {
    if (dict->first == "")
    {
      throw std::invalid_argument("<DICT ISNT OPEN>");
    }
    DictIO argument;
    in >> argument;
    if (in.fail())
    {
      throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
    }
    std::set<std::string> temp = argument.dict_el.second;
    if (dict->second.count(argument.dict_el.first) != 0)
    {
      temp = dict->second[argument.dict_el.first];
    }
    temp.merge(argument.dict_el.second);
    dict->second.insert_or_assign(argument.dict_el.first,
    temp);
    out << "#succeed#\n";
  }
  void DELETE(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
  void SEARCH(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
  void CHANGE(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
  std::istream &in, std::ostream &out)
  {
    if (dict->first == "")
    {
      throw std::invalid_argument("<DICT ISNT OPEN>");
    }
    DictIO argument;
    in >> argument;
    if (in.fail())
    {
      throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
    }
    if (dict->second.count(argument.dict_el.first) != 1)
    {
      throw std::invalid_argument("<NO SUCH KEY>");
    }
    dict->second.insert_or_assign(argument.dict_el.first, argument.dict_el.second);
    out << "#succeed#\n";
  }
  void SHOW(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
  void SHOWALL(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
}
