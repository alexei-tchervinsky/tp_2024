#include "DataStruct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
	std::vector<DataStruct> dataVec;

	std::istream_iterator<DataStruct> inputIt(std::cin);
	std::istream_iterator<DataStruct> end;
	std::copy(inputIt, end, std::back_inserter(dataVec));

	std::sort(dataVec.begin(), dataVec.end(), compareDataStruct);

	std::ostream_iterator<DataStruct> outputIt(std::cout, "\n");
	std::copy(dataVec.begin(), dataVec.end(), outputIt);

	return 0;
}