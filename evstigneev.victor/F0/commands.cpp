#include "commands.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <exception>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>

void evstigneev::help(std::ostream& out)
{
  out << "Commands:\n" <<
    "HELP - output all commands\n" <<
    "CREATE filename - creates a dicitionary for the text\n" <<
    "TOP n - output the most popular words (n - number of words)\n" <<
    "FIND word - finds the word in the dictionary\n" <<
    "MERGE filename - add words from the file\n" <<
    "REMOVE - delete the dictionary\n\n";
}

void evstigneev::create(dictionary& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (!in)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  std::string str = "";
  std::ifstream inp(name);
  if (!inp.is_open())
  {
    throw std::runtime_error("<THERE`S NO SUCH FILE>");
  }
  while (std::getline(inp, str))
  {
    std::istringstream iss(str);
    std::string t;
    while (std::getline(iss, t, evstigneev::DelimiterIO{",;.!"}))
    {
      std::transform(t.begin(), t.end(), t.begin(), std::tolower);
      dict[t]++;
    }
  }
  out << "Frequency Dictionary: " << name << '\n';
}

void evstigneev::top(dictionary& dict, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;
  if (!in)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  std::size_t words = std::stoi(cmd);
  if (words > dict.size())
  {
    throw std::runtime_error("OVERFLOW");
  }
  std::vector<std::pair<std::string, std::size_t>> ws(dict.begin(), dict.end());
  std::sort(ws.begin(), ws.end(),
    [](const std::pair<std::string, std::size_t>& f, std::pair<std::string, std::size_t>& s)
    {
      return f.second > s.second;
    });
  for (std::size_t i = 0; i < words; ++i)
  {
    out << ws[i].first << ": " << ws[i].second << '\n';
  }

}

void evstigneev::find(dictionary& dict, std::istream& in, std::ostream& out)
{
  std::string cmd = "";
  in >> cmd;
  if (!in)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  for (std::pair<std::string, std::size_t>& word : words)
  {
    if (word.first == cmd)
    {
      out << cmd << ": " << word.second << '\n'
    }
    else
    {
      out << "There`s no such word\n";
    }
  }
}

void evstigneev::merge(dictionary& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (!in)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  std::string str = "";
  std::ifstream inp(name);
  if (!inp.is_open())
  {
    throw std::runtime_error("<THERE`S NO SUCH FILE>");
  }
  while (std::getline(inp, str))
  {
    std::istringstream iss(str);
    std::string t;
    while (std::getline(iss, t, evstigneev::DelimiterIO{",;.!"}))
    {
      std::transform(t.begin(), t.end(), t.begin(), std::tolower);
      dict[t]++;
    }
  }
  out << "Frequency Dictionary is merged with: " << name << '\n';
}

void evstigneev::remove(dictionary& dict, std::ostream& out)
{
  if (dict.empty())
  {
    throw std::runtime_error("<DICTIONARY IS EMPTY>");
  }

  dict.clear();

  out << "Deleted\n";
}
