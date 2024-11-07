#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iomanip>
#include <memory>
#include <exception>
#include <fstream>
#include <limits>
#include <iterator>
#include <algorithm>
#include <functional>
#include <map>
#include <iomanip>
#include <vector>
#include "Structs.hpp"

using namespace structs;

namespace commands
{
	void HELP(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
	void OPEN(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
	void CLOSE(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
	void COMPARE(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
	void MERGE(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);

	void INSERT(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
	void DELETE(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
	void SEARCH(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
	void CHANGE(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
	void SHOW(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
	void SHOWALL(
		std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
		std::istream& in, std::ostream& out);
}
#endif
