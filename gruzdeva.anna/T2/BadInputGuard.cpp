#include "BadInputGuard.hpp"

namespace ds {
	BadInputGuard::BadInputGuard(std::basic_ios<char> &s):
		s_(s),
		precision_(s.precision()),
		flags_(s.flags())
	{}

	BadInputGuard::~BadInputGuard() {
		s_.precision(precision_);
		s_.flags(flags_);
	}
}
