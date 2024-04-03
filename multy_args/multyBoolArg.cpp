#include "multyBoolArg.hpp"
#include <iostream>

types::Result<bool> multy_args::MultyBoolArg::processWithValue(std::string value)
{
	std::cout << value << " " << usageCount << std::endl;
	return { true, true };
}
