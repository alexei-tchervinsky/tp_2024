#include "commands.h"
#include <iostream>
#include <algorithm>
#include <map>
#include "delimiter.h"
#include <exception>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>

void bekhova::help(std::ostream& out)
{
  out << "Commands:\n" <<
    "HELP - it will show all the commands that are available\n" <<
    "CREATE filename - creating a dictionary for text\n" <<
    "TOP n - displays the most popular words (n-the number of words)\n" <<
    "FIND word - searches for a word in the dictionary\n" <<
    "MERGE filename - add words from the file\n" <<
    "REMOVE - delete the dictionary\n\n";
}

void bekhova::create(dictionary& dict, std::istream& in, std::ostream& out)
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
    while (std::getline(iss, t, ',') ||
      std::getline(iss, t, '.') ||
      std::getline(iss, t, '!') ||
      std::getline(iss, t, ';'))
    {
      std::transform(t.begin(), t.end(), t.begin(), [](char c)
        {
          return std::tolower(c);
        });
      dict[t]++;
    }
  }
  out << "Frequency Dictionary: " << name << '\n';
}

void bekhova::top(dictionary& dict, std::istream& in, std::ostream& out)
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
  auto it = dict.begin();
  for (std::size_t i = 0; i < words; ++i) {
    if (it == dict.end()) {
      break;
    }
    out << it->first << ": " << it->second << '\n';
    ++it;
  }
}

void bekhova::find(dictionary& dict, std::istream& in, std::ostream& out)
{
  std::string cmd = "";
  in >> cmd;
  if (!in)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  auto it = dict.find(cmd);
  if (it != dict.end()) {
    out << cmd << ": " << it->second << '\n';
  }
  else {
    out << "There`s no such word\n";
  }
}

void bekhova::merge(dictionary& dict, std::istream& in, std::ostream& out)
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
    while (std::getline(iss, t, ',') ||
      std::getline(iss, t, '.') ||
      std::getline(iss, t, '!') ||
      std::getline(iss, t, ';'))
    {
      std::transform(t.begin(), t.end(), t.begin(), [](char c)
        {
          return std::tolower(c);
        });
      dict[t]++;
    }
  }
  out << "Frequency Dictionary is merged with: " << name << '\n';
}

void bekhova::remove(dictionary& dict, std::ostream& out)
{
  if (dict.empty())
  {
    throw std::runtime_error("<DICTIONARY IS EMPTY>");
  }

  dict.clear();

  out << "Deleted\n";
}
