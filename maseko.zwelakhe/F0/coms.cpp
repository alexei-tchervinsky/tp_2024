#include "coms.hpp"
#include "actions.hpp"

void mynspace::getHelp(std::ostream& out, std::istream& in)
{
  if (in.peek() != '\n')
  {
    throw std::invalid_argument("Error");
  }
  out << "\n1.HELP - view available commands\n";
  out << "2.CREATE <filename> - create a frequency-dictionary from the words of the <filename>\n";
  out << "3.SHOW <filename> - view a frequency-dictionary of <filename>\n";
  out << "4.TOP <filename> <-|number>\n  <->: view the top-3 most common words in the frequency-dictionary of <filename>\n";
  out << "  <number>: view the top-<number> most common words in the frequency-dictionary of <filename>\n";
  out << "5.SEARCH <filename> <WORD|NUMBER> <word|number>\n";
  out << "  <WORD> <word>: search for the <word> in the frequency-dictionary of <filename>\n";
  out << "  <NUMBER> <number>: search for a word with <number> frequency in the frequency-dictionary of <filename>\n";
  out << "6.DELETE <WORD|DICTIONARY> <filename> <word|dictionary>\n";
  out << "  <WORD> <word>: delete the <word> in the frequency-dictionary of <filename>\n";
  out << "  <DICTIONARY> <dictionary>: delete the frequency-dictionary of <filename>\n";
  out << "7.INTERSECTIONS <dictionary_1> <dictionary_2>: view the intersections of <dictionary_1> and <dictionary_2>\n";
  out << "8.MERGE <dictionary_1> <dictionary_2> <new_dictionary>: create <new_dictionary> from elements of ";
  out << "<dictionary_1> and <dictionary_2>\n";
  out << "9.ALL <DICTIONARIES|WORDS>\n  <DICTIONARIES>: view all available dictionaries\n";
  out << "  <WORDS>: view all words from dictionaries\n";
  out << "10.SAVE <dictionary> <output> - save the <dictionary> to <output>\n";
  out << "11.SORT <filename> - sort words in descending order of the number of their repetitions in the <filename>\n\n";
}

void mynspace::create(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  if (in.peek() == '\n')
  {
    throw std::invalid_argument("Error");
  }

  std::string fileName;
  in >> fileName;

  if (!in)
  {
    throw std::invalid_argument("No input file");
  }

  std::ifstream file(fileName);

  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open file");
  }

  dictionary wordFrequency;
  std::string word;

  while (file >> word)
  {
    word = toLower(word);
    word = cleanText(word);
    if (!word.empty())
    {
      ++wordFrequency[word];
    }
  }

  file.close();
  dicts[fileName] = wordFrequency;
  out << "Dictionary successfully created\n";
}

void mynspace::showDictionary(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  if (in.peek() == '\n')
  {
    throw std::invalid_argument("Error");
  }
  std::string fileName = "";
  in >> fileName;

  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }

  if (dicts.find(fileName) == dicts.end())
  {
    throw std::invalid_argument("Dictionary not found");
  }

  dictionary& dict = dicts[fileName];
  showAllWords(dict, out);
}

void mynspace::showTop(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  if (in.peek() == '\n')
  {
    throw std::invalid_argument("Error");
  }
  std::string fileName = "";
  in >> fileName;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  if (dicts.find(fileName) == dicts.end())
  {
    throw std::invalid_argument("Dictionary not found");
  }
  std::string command = "";
  in >> command;
  auto& dict = dicts.at(fileName);
  if (command == "0")
  {
    throw std::out_of_range("Invalid number");
  }
  else if (command == "-")
  {
    getTopOfNumber(dict, out, 0);
  }
  else
  {
    int topNumber;
    try
    {
      std::stringstream stream(command);
      stream >> topNumber;
      if (topNumber < 0)
      {
        throw std::out_of_range("Invalid number");
      }
      stream >> topNumber;
      getTopOfNumber(dict, out, topNumber);
    }
    catch (const std::exception& e)
    {
      throw std::invalid_argument("Incorrect number of words");
    }
  }
}

void mynspace::search(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  if (in.peek() == '\n')
  {
    throw std::invalid_argument("Error");
  }
  std::string fileName = "";
  in >> fileName;

  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }

  if (dicts.find(fileName) == dicts.end())
  {
    throw std::invalid_argument("Dictionary not found");
  }
  else
  {
    auto& dict = dicts[fileName];
    std::string command = "";
    in >> command;
    if (command == "WORD")
    {
      searchWord(dict, out, in);
    }
    else if (command == "NUMBER")
    {
      searchNumber(dict, out, in);
    }
    else
    {
      throw std::invalid_argument("Wrong  <filename> input");
    }
  }
}

void mynspace::deleteDict(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  if (in.peek() == '\n')
  {
    throw std::invalid_argument("Error");
  }

  std::string command = "";
  in >> command;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  if (command == "WORD")
  {
    deleteWord(dicts, out, in);
  }
  else if (command == "DICTIONARY")
  {
    deleteDictionary(dicts, out, in);
  }
  else
  {
    throw std::invalid_argument("Wrong command");
  }
}

void mynspace::getIntersections(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  if (in.peek() == '\n')
  {
    throw std::invalid_argument("Error");
  }
  std::string dict1 = "";
  std::string dict2 = "";
  in >> dict1 >> dict2;
  if (dicts.find(dict1) == dicts.end())
  {
    throw std::invalid_argument("Dictionary 1 not found");
  }
  if (dicts.find(dict2) == dicts.end())
  {
    throw std::invalid_argument("Dictionary 2 not found");
  }
  if (dict1 == dict2)
  {
    out << "Wrong dictionary names\n";
  }
  else
  {
    std::size_t count;
    bool flag = false;

    auto& dict1_data = dicts[dict1];
    auto& dict2_data = dicts[dict2];
    for (const auto& pair : dict1_data)
    {
      if (dict2.find(pair.first) && (dict2_data.find(pair.first) != dict2_data.end()))
      {
        count = pair.second + dict2_data[pair.first];
        out << pair.first << ": " << count << '\n';
        flag = true;
      }
    }
    if (flag)
    {
      out << "Dictionary  successfully intersected\n";
    }
    else
    {
      out << "failed to intersect dictionaries\n";
    }
  }
}

void mynspace::merge(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  if (in.peek() == '\n')
  {
    throw std::invalid_argument("Error");
  }
  std::string dict1 = "";
  std::string dict2 = "";
  std::string newDict = "";
  in >> dict1 >> dict2 >> newDict;
  if (dicts.find(dict1) == dicts.end())
  {
    throw std::invalid_argument("Dictionary 1 not found");
  }
  if (dicts.find(dict2) == dicts.end())
  {
    throw std::invalid_argument("Dictionary 2 not found");
  }
  if (dicts.find(newDict) != dicts.end())
  {
    throw std::invalid_argument("New dictionary already exists");
  }
  if ((dict1 == dict2) || (dict1 == newDict) || (dict2 == newDict))
  {
    out << "Error: matching dictionary names. Make sure dictionaries are different\n";
  }
  else
  {
    auto& dict1_data = dicts[dict1];
    auto& dict2_data = dicts[dict2];

    dicts[newDict] = {};
    auto& new_dict = dicts[newDict];

    for (const auto& pair : dict1_data)
    {
      new_dict[pair.first] = pair.second;
    }

    for (const auto& pair : dict2_data)
    {
      if (new_dict.find(pair.first) != new_dict.end())
      {
        new_dict[pair.first] += pair.second;
      }
      else
      {
        new_dict[pair.first] = pair.second;
      }
    }
    out << "Dictionaries were successfully merged\n";
  }
}

void mynspace::getAll(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  if (in.peek() == '\n')
  {
    throw std::invalid_argument("Error");
  }

  std::string command = "";
  in >> command;
  if (command == "DICTIONARIES")
  {
    showAllDictionaries(dicts, out);
  }
  else if (command == "WORDS")
  {
    std::size_t number = 1;
    for (const auto& pair : dicts)
    {
      out << number << ". " << pair.first << '\n';
      dictionary& dict_data = dicts[pair.first];
      showAllWords(dict_data, out);
      out << '\n';
      ++number;
    }
  }
  else
  {
    throw std::invalid_argument("Wrong input after <ALL>");
  }
}

void mynspace::save(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  if (in.peek() == '\n')
  {
    throw std::invalid_argument("Error");
  }
  std::string dictName = "";
  in >> dictName;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  if (dicts.find(dictName) == dicts.end())
  {
    throw std::invalid_argument("Dictionary not found");
  }
  std::string outputFileName = "";
  in >> outputFileName;
  std::ofstream file(outputFileName);
  if (!file)
  {
    throw std::invalid_argument("The file cannot be created\n");
  }
  auto& dict = dicts.at(dictName);
  for (const auto& pair : dict)
  {
    file << pair.first << ": " << pair.second << '\n';
  }
  out << "Dictionary was successfully saved to " << outputFileName << '\n';
}

void mynspace::sort(dictionaries& dicts, std::ostream& out, std::istream& in)
{
  std::string dictionaryName;
  in >> dictionaryName;

  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }

  if (dicts.find(dictionaryName) == dicts.end())
  {
    throw std::invalid_argument("Dictionary not found");
  }

  auto& dict = dicts[dictionaryName];

  std::vector< std::pair< std::string, std::size_t > > sortedDict(dict.begin(), dict.end());
  std::sort(
    sortedDict.begin(),
    sortedDict.end(),
    [](const auto& a, const auto& b)
    {
      return a.second > b.second;
    }
  );

  dict.clear();
  for (long int i = sortedDict.size() - 1; i >= 0; --i)
  {
    dict[sortedDict.at(i).first] = sortedDict.at(i).second;
  }

  out << "Dictionary was successfully sorted\n";
}