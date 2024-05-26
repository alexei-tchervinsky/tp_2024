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
  out << "create <filename> - creates Frequency Dictionary with text from the file\n";
  out << "display - shows current Frequency Dictionary\n";
  out << "top <N> - shows N most popular words\n";
  out << "findW <word> - tries to find word in the Frequency Dictionary\n";
  out << "findN <N> - tries to find words which repeats N times\n";
  out << "clear - deletes the dictionary\n";
  out << "merge <filename> - adds words from the file to existing dictionary\n";
  out << "out <filename>- export dictionary to file\n";

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

  const char* const delimiters = ", !.;";

  std::string str;
  std::ifstream input(fileName);
  if (!input.is_open())
  {
    throw std::logic_error("This file doens't exist");
  }

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

  out << "Frequency Dictionary is created from " << "'" << fileName << "'\n";
}

void leontiev::display(std::unordered_map<std::string, std::size_t>& frDict, std::ostream& out)
{
   if (frDict.size() == 0)
  {
    throw std::logic_error("Dictionary is empty");
  }

  out << "Current Frequency Dictionary: " << "\n";

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
  std::string argument = "";
  if (!(in >> argument))
  {
    throw std::logic_error("Invalid argument");
  }

  if (frDict.size() == 0)
  {
    throw std::logic_error("Dictionary is empty");
  }

  std::size_t wordAmount = std::stoi(argument);
  if (wordAmount > frDict.size())
  {
    throw std::logic_error("Given number is too big");
  }

  std::vector<std::pair<std::string, std::size_t>> vec(frDict.begin(), frDict.end());
  std::sort(vec.begin(), vec.end(), comparator);

  for (std::size_t i = vec.size()-1; i > vec.size()-1 - wordAmount; --i)
  {
    out << vec[i].first << ": " << vec[i].second << "\n";
  }
}

void leontiev::findWord(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (!in)
  {
    throw std::logic_error("Wrong input");
  }

  if (frDict.size() == 0)
  {
    throw std::logic_error("Dictionary is empty");
  }

  bool isFound = false;

  for (auto element : frDict)
  {
    if (element.first == argument)
    {
      isFound = true;
      out << "This word repeats " << element.second << " times\n";
    }
  }

  if (!isFound)
  {
    out << "There are no such words in text\n";
  }
}

void leontiev::clear(std::unordered_map<std::string, std::size_t>& frDict, std::ostream& out)
{
  if (frDict.size() == 0)
  {
    throw std::logic_error("Dictionary is empty");
  }

  frDict.clear();

  out << "Dictionary is deleted\n";
}

void leontiev::merge(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out)
{
  std::string fileName = "";
  in >> fileName;
  if (!in)
  {
    throw std::logic_error("Invalid argument");
  }

  if (frDict.size() == 0)
  {
    throw std::logic_error("Dictionary is empty");
  }

  const char* const delimiters = ", !.;";

  std::string str;
  std::ifstream input(fileName);
  if (!input.is_open())
  {
    throw std::logic_error("This file doens't exist");
  }

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

  out << "Frequency Dictionary is merged with file " << "'" << fileName << "'\n";
}

void leontiev::findN(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (!in)
  {
    throw std::logic_error("Wrong input");
  }

  if (frDict.size() == 0)
  {
    throw std::logic_error("Dictionary is empty");
  }

  bool isFound = false;
  std::size_t N = std::stoi(argument);
  for (auto element : frDict)
  {
    if (element.second == N)
    {
      isFound = true;
      out << "Word '" << element.first << "' repeats "<< N << " times\n";
    }
  }

  if (!isFound)
  {
    out << "There are no such words in text\n";
  }
}

void leontiev::out(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (!in)
  {
    throw std::logic_error("Wrong input");
  }

  if (frDict.size() == 0)
  {
    throw std::logic_error("Dictionary is empty");
  }

  std::ofstream output(argument);
  if (!output)
  {
    throw std::logic_error("File creation error");
  }

  for (auto it = frDict.begin(); it != frDict.end(); ++it)
  {
    output << it->first << ": " << it->second << "\n";
  }
  out << "Dictionary is exported\n";
}
