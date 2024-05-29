#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <list>
#include <map>
#include <memory>

namespace commands {
  void help(std::ostream& os);
  void getAllDictionaries(
      const std::map<std::string, std::shared_ptr<std::map<std::string,std::list<int>>>>& dictionaries,
      std::ostream& os);
  void create(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
              std::string& currentDict,
              std::istream& is, std::ostream& os);
  void rename(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
              std::istream& is, std::ostream& os);
  void del(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
           std::istream& is, std::ostream& os);
  void changeCurrentDictionary(
      std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
      std::string& currentDict,
      std::istream& is, std::ostream& os);
  void count(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
             const std::string& currentDict, std::ostream& os);
  void search(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
              const std::string& currentDict,
              std::istream& is, std::ostream& os);
  void print(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
             const std::string& currentDict,
             std::ostream& os);
  void remove(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
              std::string& currentDict,
              std::istream& is, std::ostream& os);
  void save(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
            const std::string& currentDict,
            std::istream& is, std::ostream& os);

  std::ostream& outError(std::ostream& os, const std::string& message);
}

#endif //COMMANDS_HPP
