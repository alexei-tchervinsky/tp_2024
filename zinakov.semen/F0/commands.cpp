#include <algorithm>
#include <exception>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "commands.hpp"

void semzin::commands(std::ostream &out)
{
  out << "1)commands - displays list of available commands.\n";
  out << "2)make <filename> - creates new frequency dictionary with text from the file named filename.\n";
  out << "3)print - shows dictionary contents.\n";
  out << "4)sortMtoL - displays the dictionary from the most popular word to the least popular.\n";
  out << "5)sortLtoM - displays the dictionary from the least popular word to the most popular.\n";
  out << "6)holyTrinityMost - shows 3 most popular words.\n";
  out << "7)holyTrinityLeast - shows 3 least popular words.\n";
  out << "8)find <word> - finds word in the dictionary.\n";
  out << "9)remove <word> - deletes word from the dictionary.\n";
  out << "10)deleteDict - deletes the dictionary.\n";
  out << "11)save <filename> - saves dictionary to file.\n";

  out << "\n";
}

void semzin::make(std::unordered_map<std::string, std::size_t> &frequencyDict, std::istream &in, std::ostream &out)
{
  if (in.get() == '\n')
  {
    throw std::logic_error("Error: parameter required!");
  }
  std::string filename = "";
  in >> filename;
  std::ifstream input(filename);
  if (!input.is_open())
  {
    throw std::logic_error("Error: such file doesn't exist");
  }

  std::string str = "";
  const char *delims = " ,.!;?";
  while (std::getline(input, str))
  {
    char *lexema = std::strtok(strdup(str.c_str()), delims);
    while (lexema)
    {
      lexema[0] = std::tolower(lexema[0]);
      frequencyDict[lexema]++;
      lexema = std::strtok(nullptr, delims);
    }
  }
  out << "Dictionary successfully created.\n\n";
}

void semzin::sortMtoL(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out)
{
  if (frequencyDict.size() == 0)
  {
    throw std::logic_error("Error: dictionary is empty!");
  }

  out << "----- Dictionary format: word - [frequency] -----" << "\n";
  std::vector<std::pair<std::string, std::size_t>> vec(frequencyDict.begin(), frequencyDict.end());
  std::sort(vec.begin(), vec.end(), comparatorMax);

  for (std::size_t i = 0; i < vec.size(); ++i)
  {
    out << vec[i].first << " - [" << vec[i].second << "]\n";
  }
  out << "\n";
}

void semzin::sortLtoM(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out)
{
  if (frequencyDict.size() == 0)
  {
    throw std::logic_error("Error: dictionary is empty!");
  }

  out << "----- Dictionary format: word - [frequency] -----" << "\n";
  std::vector<std::pair<std::string, std::size_t>> vec(frequencyDict.begin(), frequencyDict.end());
  std::sort(vec.begin(), vec.end(), comparatorMin);

  for (std::size_t i = 0; i < vec.size(); ++i)
  {
    out << vec[i].first << " - [" << vec[i].second << "]\n";
  }
  out << "\n";
}

void semzin::print(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out)
{
  if (frequencyDict.size() == 0)
  {
    throw std::logic_error("Error: dictionary is empty!");
  }

  out << "----- Dictionary format: word - [frequency] -----" << "\n";
  for (auto it = frequencyDict.begin(); it != frequencyDict.end(); ++it)
  {
    out << it->first << " - [" << it->second << "]\n";
  }
  out << '\n';
}

bool semzin::comparatorMax(const std::pair<std::string, std::size_t> &currPair, const std::pair<std::string, std::size_t> &nextPair)
{
  return currPair.second > nextPair.second;
}
bool semzin::comparatorMin(const std::pair<std::string, std::size_t> &currPair, const std::pair<std::string, std::size_t> &nextPair)
{
  return currPair.second < nextPair.second;
}

void semzin::holyTrinityMost(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out)
{
  if (frequencyDict.size() == 0)
  {
    throw std::logic_error("Error: dictionary is empty!");
  }
  std::vector<std::pair<std::string, std::size_t>> vec(frequencyDict.begin(), frequencyDict.end());
  std::sort(vec.begin(), vec.end(), comparatorMax);

  for (std::size_t i = 0; i < 3; ++i)
  {
    out << vec[i].first << " - [" << vec[i].second << "]\n";
  }
  out << '\n';
}

void semzin::holyTrinityLeast(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out)
{
  if (frequencyDict.size() == 0)
  {
    throw std::logic_error("Error: dictionary is empty!");
  }
  std::vector<std::pair<std::string, std::size_t>> vec(frequencyDict.begin(), frequencyDict.end());
  std::sort(vec.begin(), vec.end(), comparatorMin);

  for (std::size_t i = 0; i < 3; ++i)
  {
    out << vec[i].first << " - [" << vec[i].second << "]\n";
  }
  out << '\n';
}

void semzin::findWord(std::unordered_map<std::string, std::size_t> &frequencyDict, std::istream &in, std::ostream &out)
{
  if (in.get() == '\n')
  {
    throw std::logic_error("Error: parameter required!");
  }
  if (frequencyDict.size() == 0)
  {
    throw std::logic_error("Error: dictionary is empty!");
  }

  std::string parameter = "";
  in >> parameter;
  bool isFound = false;
  for (auto pair : frequencyDict)
  {
    if (parameter == pair.first)
    {
      isFound = true;
      if (pair.second == 1)
      {
        out << "The word '" << parameter << "' appears " << pair.second << " time\n\n";
      }
      else
      {
        out << "The word '" << parameter << "' appears " << pair.second << " times\n\n";
      }
    }
  }
  if (!isFound)
  {
    out << "There is no such word in dictionary!\n\n";
  }
}

void semzin::removeWord(std::unordered_map<std::string, std::size_t> &frequencyDict, std::istream &in, std::ostream &out)
{
  if (in.get() == '\n')
  {
    throw std::logic_error("Error: parameter required!");
  }
  if (frequencyDict.size() == 0)
  {
    throw std::logic_error("Error: dictionary is empty!");
  }

  std::string parameter = "";
  in >> parameter;
  bool isFound = false;
  for (auto pair : frequencyDict)
  {
    if (parameter == pair.first)
    {
      isFound = true;
      frequencyDict.erase(parameter);
      out << "The word '" << parameter << "' successfully deleted!\n\n";
      break;
    }
  }
  if (!isFound)
  {
    out << "There is no such word in text!\n\n";
  }
}

void semzin::remove(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out)
{
  frequencyDict.clear();
  out << "Dictionary successfully deleted.\n\n";
}

void semzin::save(std::unordered_map<std::string, std::size_t> &frequencyDict, std::istream &in, std::ostream &out)
{
  if (in.get() == '\n')
  {
    throw std::logic_error("Error: parameter required!");
  }
  if (frequencyDict.size() == 0)
  {
    throw std::logic_error("Error: dictionary is empty!");
  }

  std::string parameter = "";
  in >> parameter;
  std::ofstream ofs(parameter);

  for (auto it = frequencyDict.begin(); it != frequencyDict.end(); ++it)
  {
    ofs << it->first << " - [" << it->second << "]\n";
  }
  out << "Dictionary successfully saved in file named '" << parameter << "'.\n\n";
}
