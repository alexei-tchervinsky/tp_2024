#include "Commands.h"

using namespace std::placeholders;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "file name not included\n";
    return 1;
  }
  std::ifstream in;
  in.open(argv[1]);
  if (!in)
  {
    std::cerr << "file nor found\n";
    return 1;
  }
  std::vector< grudov::Polygon > polygons;
  while (!in.eof())
  {
    std::copy(std::istream_iterator< grudov::Polygon >(in),
    std::istream_iterator< grudov::Polygon >(),
    std::back_inserter(polygons));
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::map< std::string, std::function< void(const std::vector< grudov::Polygon >, std::istream &, std::ostream &) > > cmds;
  {
    cmds["AREA"] = std::bind(grudov::area, _1, _2, _3);
    cmds["MAX"] = std::bind(grudov::max, _1, _2, _3);
    cmds["MIN"] = std::bind(grudov::min, _1, _2, _3);
    cmds["COUNT"] = std::bind(grudov::count, _1, _2, _3);
    cmds["RECTS"] = std::bind(grudov::rects, _1, _2, _3);
    cmds["MAXSEQ"] = std::bind(grudov::maxseq, _1, _2, _3);
  };

  std::string command = "";
  while (std::cin >> command) {
    try {
      cmds.at(command)(polygons, std::cin, std::cout);
    }
    catch (const std::exception& ex)
    {
      std::cout << ex.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
