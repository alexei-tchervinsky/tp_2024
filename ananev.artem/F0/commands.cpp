#include "Commands.hpp"

namespace commands
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
    in >> c;
    if (in && (c != dest.del))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  void OPEN(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::vector<std::string> > > > dict,
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
    std::map< std::string, std::vector<std::string> > input_dict;
    std::string key;
    std::string temp = "";
    std::vector <std::string> translation;
    while (!input_file.eof())
    {
      input_file >> DelimiterIO{'{'};
      input_file >> key;
      input_file >> DelimiterIO{'-'};
      while (true)
      {
        char c;
        input_file >> c;
        if (c != ';' && c != '}' && c != '\n' && c != '\0')
        {
          temp += c;
        }
        else if (c == ';')
        {
          translation.push_back(temp);
          temp = "";
        }
        else if (c == '}')
        {
          translation.push_back(temp);
          temp = "";
          break;
        }
        else
        {
          input_file.setstate(std::ios::failbit);
          break;
        }
      }
      if (input_file.fail())
      {
        input_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        key = "";
        temp = "";
        translation.clear();
        continue;
      }
      if (key != "")
      {
        input_dict[key] = translation;
      }
      key = "";
      temp = "";
      translation.clear();
    }
    dict->first = input_name;
    dict->second = input_dict;
  }

  void CLOSE(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::vector<std::string> > > > dict,
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
      throw std::invalid_argument("<DICT IST OPENED>");
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
        for (std::size_t i = 0; i < pair->second.size(); i++)
        {
          if (i == pair->second.size()-1)
          {
            output_file << " " << pair->second[i] << "}\n";
          }
          else
          {
            output_file << " " << pair->second[i] << ";";
          }
        }
      }
    }
    else if (save != "N")
    {
      throw std::invalid_argument("<EXCESS ARGUMENT>");
    }
    dict->first = "";
    dict->second.clear();
  }
  void COMPARE(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::vector<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}

  void INSERT(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::vector<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
  void DELETE(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::vector<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
  void SEARCH(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::vector<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
  void CHANGE(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::vector<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
  void SHOW(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::vector<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
  void SHOWALL(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::vector<std::string> > > > dict,
  std::istream &in, std::ostream &out){std::cout <<"";}
}
