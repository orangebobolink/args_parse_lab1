#include "userDemoArg.hpp"
#include <regex>

types::Result<bool> IpValidator::validate(std::string& value)
{
	const static  std::regex pattern("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

	return { std::regex_match(value, pattern) };
}
