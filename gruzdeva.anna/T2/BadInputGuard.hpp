#ifndef BAD_INPUT_HPP
#define BAD_INPUT_HPP

#include <iostream>

namespace ds {
	class BadInputGuard {
	public:
		explicit BadInputGuard(std::basic_ios<char>& s);
			~BadInputGuard();
		private:
			std::basic_ios<char>& s_;
			std::streamsize precision_;
			std::basic_ios<char>::fmtflags flags_;
		};
}

#endif //BAD_INPUT_HPP
