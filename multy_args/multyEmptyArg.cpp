#include "multyEmptyArg.hpp"
#include <iostream>

types::Result<bool> multy_args::MultyEmptyArg::process()
{
	std::cout << usageCount << std::endl;

	return args::EmptyArg::process();
}
