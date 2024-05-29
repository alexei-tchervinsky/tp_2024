#include "commands.hpp"

void berezneva::info(std::ostream& out)
{
  out << "Commands for En_Rus_Dictionary:\n"
    << "info - see all available commands\n"
    << "create <filename.txt> - create dictionary from <filename.txt> \n"
    << "remove <dictionary_name> - delete dictionary <dictionary_name>\n"
    << "search <dictionary_name> <word> - search all translations of <word> in dictionary <dictionary_name>\n"
    << "rename <old_name> <new_name> - swap names from <old_name> to <new_name>\n"
    << "names - see all names of dictionaries\n"
    << "count <dictionary_name> - amount of words in dictionary\n";
}


untitledDict berezneva::input(std::istream& in)
{
  untitledDict dict;
  Dict newPair;

  while (!in.eof())
  {
    in >> newPair;

    if (in.fail() && !in.eof())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    dict[newPair.str_.first] = newPair.str_.second;
  }

  return dict;
}

void berezneva::create(DictMap& Dicts, std::istream& in, std::ostream& out)
{
  std::string fileName;
  in >> fileName;

  if (Dicts.find(fileName) != Dicts.end())
    throw std::invalid_argument("Dictionary already exists");
  else
  {
    untitledDict dict;

    if (fileName.find(".txt") != std::string::npos)
    {
      std::ifstream input;
      input.open(fileName);

      if (input.is_open())
      {
        std::size_t start{ fileName.find(".txt") };
        std::string dictName = fileName.replace(start, start + 4, "");
        dict = berezneva::input(input);
        Dicts.emplace(dictName, dict);
      }
      else
        throw std::out_of_range("Cannot open file");

      input.close();
    }
    else
    {
      Dicts.emplace(fileName, dict);
    }

    out << "Dictionary was created\n";
  }
}

void berezneva::remove(DictMap& Dicts, std::istream& in, std::ostream& out)
{

  std::string name;
  in >> name;

  if (Dicts.erase(name))
    out << "Deleted.\n";
  else
    out << "Not deleted.\n";
}

void berezneva::search(DictMap& Dicts, std::istream& in, std::ostream& out)
{
  std::string name, key;
  in >> name;
  in >> key;

  if (name == "")
    throw std::invalid_argument("No dictionary is chosen");

  if (key == "")
    throw std::invalid_argument("Expected a word");

  if (Dicts.count(name) == 1)
  {
    untitledDict tempDict = Dicts.find(name)->second;
    auto tempDictStr = tempDict.find(key);

    if (tempDictStr != tempDict.end())
    {
      out << "{ " << tempDictStr->first << " - ";

      for (auto i = tempDictStr->second.begin(); i != tempDictStr->second.end(); i++)
        out << *i << "; ";

      out << "}" << '\n';
    }
    else
      out << "No such word in the dictionary" << '\n';
  }
  else
    throw std::logic_error("No such dictionary");
}

void berezneva::rename(DictMap& Dicts, std::istream& in, std::ostream& out)
{
  std::string oldName, newName;
  in >> oldName;
  in >> newName;

  if (Dicts.find(newName) == Dicts.end())
  {
    auto dictOldName = Dicts.find(oldName);
    Dicts.emplace(newName, dictOldName->second);
    Dicts.erase(dictOldName);
    out << "Dictionary '" << oldName << "' was renamed to '" << newName << '\n';
  }
  else
    out << "Dictionary wasn't found.\n";
}

void berezneva::allDictNames(DictMap& Dicts, std::ostream& out)
{
  if (Dicts.empty())
    out << "There is no one dictionary.\n";
  else
  {
    std::size_t number = 1;

    for (auto i = Dicts.begin(); i != Dicts.end(); ++i)
    {
      out << number << ". " << i->first << '\n';
      ++number;
    }
  }
}

void berezneva::countWords(DictMap& Dicts, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;

  if (name == "")
    throw std::invalid_argument("No dictionary is chosen");

  if (Dicts.count(name) == 1)
  {
    std::size_t count = 0;
    untitledDict nessDict = Dicts.find(name)->second;

    for (auto i = nessDict.begin(); i != nessDict.end(); i++)
      ++count;

    out << count << " words.\n";
  }
  else
    throw std::logic_error("No such dictionary");
}
