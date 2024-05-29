#ifndef INOUTPUT_H
#define INOUTPUT_H

#include <iosfwd>
#include "delimiterIO.h"
#include "ullBinIO.h"
#include "ullLitIO.h"
#include "stringIO.h"
#include "delStrIO.h"
#include "dataStruct.h"

namespace bylinskiy {
	std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
	std::istream& operator>>(std::istream& in, UllBinIO&& dest);
	std::istream& operator>>(std::istream& in, UllLitIO&& dest);
	std::istream& operator>>(std::istream& in, StringIO&& dest);
	std::istream& operator>>(std::istream& in, DelStrIO&& dest);
	std::istream& operator>>(std::istream& in, DataStruct& dest);
	std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}

#endif