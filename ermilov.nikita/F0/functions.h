#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <list>
#include <unordered_map>

namespace ermilov
{
  bool correctEng(const std::string word);
  bool correctRus(const std::string word);
  std::string subTranslate(const std::list<std::string>& translates);

  void insert(std::unordered_multimap<std::string, std::list<std::string>>& map, std::istream& in, std::ostream& out);
  void deleteWord(std::unordered_multimap<std::string, std::list<std::string>>& map, std::istream& in, std::ostream& out);
  void translate(std::unordered_multimap<std::string, std::list<std::string>> map, std::istream& in, std::ostream& out);
}
#endif // !FUNCTIONS_H
