#include "functions.hpp"

std::string gredasov::getText(const char * file)
{
  std::ifstream in(file);
  std::string data;
  data.assign((std::istreambuf_iterator<char>(in.rdbuf())), std::istreambuf_iterator<char>());

  toLower(data);
  return data;
}

std::string gredasov::toLower(std::string text)
{
  std::transform(
    text.begin(),
    text.end(),
    text.begin(),
    [](char c)
    {
      return std::tolower(c);
    }
  );
  return text;
}

std::string gredasov::cleanText(std::string text)
{
  text.erase(remove_if(text.begin(), text.end(), ispunct), text.end());
  text.erase(remove_if(text.begin(), text.end(), isspace), text.end());
  return text;
}

void gredasov::getTopOfNumber(dictionary& dict, std::ostream& out, int number)
{
  if (number == 0)
  {
    number = 3;
  }

  std::vector< std::pair< std::string, std::size_t > > sortedDict(dict.begin(), dict.end());
  std::sort(
    sortedDict.begin(),
    sortedDict.end(),
    [](const auto& a, const auto& b)
    {
      return a.second > b.second;
    }
  );

  int i = 0;
  for (const auto& pair : sortedDict)
  {
    out << pair.first << ": " << pair.second << '\n';
    if (++i == number)
    {
      break;
    }
  }
}

void gredasov::searchWord(dictionary& dict, std::ostream& out, std::istream& in)
{
  std::string word;
  in >> word;
  if (!in)
  {
    throw std::invalid_argument("Wrong input after WORD");
  }
  if (dict.find(word) == dict.end())
  {
    out << "No such word in the dictionary\n";
  }
  else
  {
    for (const auto& pair : dict)
    {
      if (pair.first == word)
      {
        out << pair.first << ": " << pair.second << '\n';
      }
    }
  }
}

void gredasov::searchNumber(dictionary& dict, std::ostream& out, std::istream& in)
{
  std::size_t number;
  in >> number;
  if (!in)
  {
    throw std::invalid_argument("Wrong input after WORD");
  }
  bool flag = false;
  for (const auto& pair : dict)
  {
    if (pair.second == number)
    {
      out << pair.first << ": " << pair.second << '\n';
      flag = true;
    }
  }
  if (!flag)
  {
    out << "No word with this frequency in the dictionary\n";
  }
}

void gredasov::deleteWord(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  std::string fileName = "";
  in >> fileName;
  if (dicts.find(fileName) == dicts.end())
  {
    throw std::invalid_argument("Dictionary not found");
  }
  std::string word = "";
  in >> word;
  auto& dict = dicts[fileName];
  if (dict.find(word) == dict.end())
  {
    out << "No such word in the dictionary\n";
  }
  else
  {
    if (dict.erase(word) > 0)
    {
      out << "The word was deleted\n";
    }
    else
    {
      out << "The word cannot be deleted\n";
    }
  }
}

void gredasov::deleteDictionary(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  std::string fileName = "";
  in >> fileName;
  if (dicts.find(fileName) == dicts.end())
  {
    throw std::invalid_argument("Dictionary not found");
  }
  if (dicts.erase(fileName) > 0)
  {
    out << "Dictionary was deleted\n";
  }
  else
  {
    out << "Dictionary cannot be deleted\n";
  }
}

void gredasov::showAllDictionaries(dictionaries& dicts, std::ostream& out)
{
  if (dicts.empty())
  {
    throw std::invalid_argument("No dictionaries found");
  }
  std::size_t num = 1;
  for (const auto& pair : dicts)
  {
    out << num << ". " << pair.first << '\n';
    ++num;
  }
}

void gredasov::showAllWords(dictionary& dict, std::ostream& out)
{
  for (const auto& pair : dict)
  {
    out << pair.first << ": " << pair.second << '\n';
  }
}

