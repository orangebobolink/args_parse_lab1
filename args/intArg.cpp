#include "intArg.hpp"

namespace args
{
	bool IntArg::validateValue(std::string value)
	{
		std::string::const_iterator it = value.begin();

		while (it != value.end() && std::isdigit(*it)) ++it;

		return !value.empty() && it == value.end();
	}
}
