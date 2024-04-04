#include "multyBoolArg.hpp"
#include <iostream>

types::Result<bool> multy_args::MultyBoolArg::process()
{
	std::cout << this->value << " " << usageCount << std::endl;
	return { true, true };
}
