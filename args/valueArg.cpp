#include "valueArg.hpp"
#include <iostream>

bool args::ValueArg::validateValue(std::string value)
{
	return true;
}

types::Result<bool> args::ValueArg::process()
{
	std::cout << this->getShortArg() << this->value << std::endl;
	return { true, true };
}
