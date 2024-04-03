#include "emptyArg.hpp"

bool args::EmptyArg::validateValue(std::string value)
{
	return true;
}

types::Result<bool> args::EmptyArg::process()
{
	return args::Arg::process();
}
