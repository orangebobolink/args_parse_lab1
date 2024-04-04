#include "multyIntArg.hpp"
#include <iostream>

types::Result<bool> multy_args::MultyIntArg::processWithValue(std::string value)
{
	std::cout << value << " " << usageCount << std::endl;

	return { true, true };
}
