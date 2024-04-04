#include "multyStringArg.hpp"

#include <iostream>

types::Result<bool> multy_args::MultyStringlArg::process()
{
	std::cout << value << " " << usageCount << std::endl;

	return { true, true };
}
