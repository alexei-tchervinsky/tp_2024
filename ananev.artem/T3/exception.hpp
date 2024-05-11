#ifndef EX_HPP
#define EX_HPP
#include <exception>
#include <string>
#include <iostream>

namespace ananev
{
	class InvalidCommand : public std::exception
	{
	public:
		InvalidCommand() : reason_("<INVALID COMMAND>") {}
		const char* what() const noexcept override { return reason_.c_str(); }
	private:
		const std::string reason_;
	};
}

#endif
