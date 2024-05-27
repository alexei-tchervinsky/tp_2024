#include <iostream>
#include <iterator> // istream_iterator
#include <limits> // numeric_limits
#include <map> // map
#include <functional> // function
#include <sstream> // istringstream

#include "command.hpp"
#include "function.hpp"

using namespace kladkovoj;

int main(int argc, char *argv[])
{
  std::map<std::string, std::function<void(const std::vector<std::string>&)>> commandMap =
  {
    {"HELP", [](const std::vector<std::string>&) { command::help(); }},
    {"CREATE", [](const std::vector<std::string>& tokens)
    {
      if (tokens.size() == 2)
        command::create(tokens[1]);
      else if (tokens.size() == 4)
      {
        int capacity = std::stoi(tokens[1]);
        int numItems = std::stoi(tokens[2]);
        command::create(capacity, numItems, tokens[3]);
      }
      else
        std::cerr << "Invalid usage. Type HELP for a list of commands.\n";
    }},
    {"SHOW", [](const std::vector<std::string>& tokens) { command::show(tokens); }},
    {"SOLVE_DP", [](const std::vector<std::string>& tokens)
    {
      if (tokens.size() == 2)
        command::solveDP(tokens[1]);
      else
        throw std::invalid_argument("SOLVE_DP requires a filename.");
    }},
    {"SOLVE_BT", [](const std::vector<std::string>& tokens)
    {
      if (tokens.size() == 2)
        command::solveBT(tokens[1]);
      else
        throw std::invalid_argument("SOLVE_BT requires a filename.");
    }},
    {"SOLVE_BB", [](const std::vector<std::string>& tokens)
    {
      if (tokens.size() == 2)
        command::solveBB(tokens[1]);
      else
        throw std::invalid_argument("SOLVE_BB requires a filename.");
    }},
    {"SOLVE_BF", [](const std::vector<std::string>& tokens)
    {
      if (tokens.size() == 2)
        command::solveBF(tokens[1]);
      else
        throw std::invalid_argument("SOLVE_BF requires a filename.");
    }}
  };

  std::string line;
  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);

    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    if (tokens.empty())
      continue;

    try
    {
      auto it = commandMap.find(tokens[0]);
      if (it != commandMap.end())
        it->second(tokens);
      else if (!tokens[0].empty())
        throw std::invalid_argument("<INVALID COMMAND>");
    }
    catch (std::exception &e)
    {
      std::cout << e.what() << '\n';
    }

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
