#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "functions.h"

typedef std::unordered_multimap<std::string, std::list<std::string>>::iterator unit;

namespace ermilov
{
  bool correctEng(const std::string word)
  {
    if (word.size() == 0)
    {
      return false;
    }
    for (int i = 0; i < word.size(); i++)
    {
      if (word[i] < 'A' || word[i] > 'Z' && word[i] < 'a' || word[i] > 'z')
      {
        return false;
      }
    }
    return true;
  }

  bool correctRus(const std::string word)
  {
    if (word.size() == 0)
    {
      return false;
    }
    for (int i = 0; i < word.size(); i++)
    {
      if (word[i] < 'À' || word[i] > 'ï' && word[i] < 'ð' || word[i] > 'ÿ')
      {
        return false;
      }
    }
    return true;
  }

  std::string subTranslate(const std::list<std::string>& translates)
  {
    const char* delimeter = " OR ";
    std::ostringstream strStream;
    std::copy(translates.begin(), translates.end(),
      std::ostream_iterator<std::string>(strStream, delimeter));

    std::string result = strStream.str();
    result.erase(result.end() - 4, result.end());
    return result;
  }

  void insert(std::unordered_multimap<std::string, std::list<std::string>>& map, std::istream& in, std::ostream& out)
  {
    std::string newEng, newRus;

    in >> newEng;
    if (!correctEng(newEng))
    {
      throw std::invalid_argument("");
    }
    while (in.peek() != '\n' && !in.eof())
    {
      in >> newRus;
      if (!correctRus(newRus))
      {
        out << "Incorrect word " << newRus << ", translation not added.\n\n";
        continue;
      }

      auto found = map.find(newEng);
      if (found != map.end())
      {
        std::list<std::string>::iterator lIter = std::find(found->second.begin(), found->second.end(), newRus);
        if (lIter == found->second.end())
        {
          found->second.push_back(newRus);
          found->second.sort();
        }
      }
      else
      {
        std::list<std::string> tranlates;
        tranlates.push_back(newRus);
        std::pair<std::string, std::list<std::string>> pair(newEng, tranlates);
        map.insert(pair);
      }

      std::ofstream file("words.txt", std::ios_base::app);
      file << ' ' << newEng << ' ' << newRus;
      file.close();
    }
    if (newRus == "")
    {
      out << "<INVALID COMMAND>\n\n";
    }
    out << '\n';
  }

  void deleteWord(std::unordered_multimap<std::string, std::list<std::string>>& map, std::istream& in, std::ostream& out)
  {
    std::string deleteEng;

    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }
    in >> deleteEng;

    auto found = map.find(deleteEng);
    if (!correctEng(deleteEng))
    {
      throw std::invalid_argument("");
    }
    else if (found == map.end())
    {
      out << "Error! No such word in dictionary.\n\n";
    }
    else
    {
      unit iter = map.find(deleteEng);
      std::string deleteRus = subTranslate(iter->second);
      map.erase(deleteEng);

      std::ifstream ifile("words.txt");
      std::string buffer, wordsList;

      ifile.seekg(0, ifile.beg);

      while (!ifile.eof())
      {
        ifile >> buffer;
        if (buffer != deleteEng && deleteRus.find(buffer) == std::string::npos)
        {
          wordsList.append(buffer);
          wordsList += ' ';
        }
      }
      std::ofstream ofile("words.txt");
      ofile << wordsList;
    }
    out << '\n';
  }

  void translate(std::unordered_multimap<std::string, std::list<std::string>> map, std::istream& in, std::ostream& out)
  {
    std::string word;
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }
    in >> word;

    if (in.peek() != '\n' && !in.eof())
    {
      throw std::invalid_argument("");
    }
    if (correctEng(word))
    {
      auto found = map.find(word);
      if (found != map.end())
      {
        unit iter = map.find(word);
        out << "Translation:        " << subTranslate(iter->second) << "\n\n";
      }
      else
      {
        out << "There is no such word in the dictionary!\n\n";
      }
    }
    else
    {
      out << "Incorrect word! Try again using capitalized English words!\n\n";
    }
  }
}
