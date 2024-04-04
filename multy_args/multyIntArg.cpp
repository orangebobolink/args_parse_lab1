#include "multyIntArg.hpp"
#include <iostream>

types::Result<bool> multy_args::MultyIntArg::process()
{
	std::cout << this->value << " " << usageCount << std::endl;

	return { true, true };
}
