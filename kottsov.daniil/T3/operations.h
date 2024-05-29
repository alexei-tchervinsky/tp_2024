#include "polygon.h"
#include <map>
#include <functional>
#include <string>
#include <iomanip>
#include <exception>
#include <cctype>
#include <limits>

#ifndef OPERATIONS
#define OPERATIONS
namespace poly
{
  struct ExpressionIO
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream& in, ExpressionIO&& exp);
  void ioUI(std::vector<Polygon>& vector, std::istream& in, std::ostream& out);
  double getTotalArea(const std::vector<Polygon>& vector, bool type);
  double getMeanArea(const std::vector<Polygon>& vector);
  double getSpecArea(const std::vector<Polygon>& vector, size_t num);
  double getMaxArea(const std::vector<Polygon>& vector);
  size_t getMaxVert(const std::vector<Polygon>& vector);
  double getMinArea(const std::vector<Polygon>& vector);
  size_t getMinVert(const std::vector<Polygon>& vector);
  size_t countTotal(const std::vector<Polygon>& vector, bool type);
  size_t countSpec(const std::vector<Polygon>& vector, size_t num);
  size_t rmecho(std::vector<Polygon>& vector, const Polygon& plg);
  size_t same(const std::vector<Polygon>& vector, const Polygon& plg);
};
#endif
