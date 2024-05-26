#include <algorithm>
#include <exception>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "commands.hpp"

void leontiev::help(std::ostream& out)
{
  out << "Available commands: \n";
  out << "create <filename> - creates Frequence Dictionary with text from the file\n";
  out << "display - shows current Frequence Dictionary\n";
  out << "top <N> - shows N most popular words\n";

  out << "\n";
}

void leontiev::create(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out)
{
  std::string fileName = "";
  in >> fileName;
  if (!in)
  {
    throw std::logic_error("Invalid argument");
  }
  const char* const delimiters = ", !.";
  std::string str;
  std::ifstream input(fileName);
  while (std::getline(input, str))
  {
    char* token = std::strtok(strdup(str.c_str()), delimiters);
    while (token != nullptr)
    {
      token[0] = std::tolower(token[0]);
      frDict[token]++;
      token = std::strtok(nullptr, delimiters);
    }
  }
  out << "Frequence Dictionary is created from " << "'" << fileName << "'\n";
}

void leontiev::display(std::unordered_map<std::string, std::size_t>& frDict, std::ostream& out)
{
  out << "Current Frequence Dictionary: " << "\n";
  for (auto it = frDict.begin(); it != frDict.end(); ++it)
  {
    out << it->first << ": " << it->second << "\n";
  }
}

bool comparator(const std::pair<std::string, std::size_t>& first, const std::pair<std::string, std::size_t>& second)
{
  return first.second < second.second;
}

void leontiev::top(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out)
{
  if (frDict.size() == 0)
  {
    throw std::logic_error("Dictionary is empty");
  }
  std::string argument = "";
  if (!(in >> argument))
  {
    throw std::logic_error("Invalid argument");
  }
  std::size_t wordAmount = std::stoi(argument);
  if (wordAmount > frDict.size())
  {
    throw std::logic_error("Given number is too big");
  }
  std::vector<std::pair<std::string, std::size_t>> vec(frDict.begin(), frDict.end());
  std::sort(vec.begin(), vec.end(), comparator);
  for (std::size_t i = vec.size()-1; i >= vec.size()-1 - wordAmount; --i)
  {
    out << vec[i].first << ": " << vec[i].second << "\n";
  }
}
