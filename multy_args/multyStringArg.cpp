#include "multyStringArg.hpp"

#include <iostream>

types::Result<bool> multy_args::MultyStringlArg::processWithValue(std::string value)
{
	std::cout << value << " " << usageCount << std::endl;

	return { true, true };
}
