#include "stringArg.hpp"

namespace args
{
	bool StringArg::validateValue(std::string value)
	{
		for (const char c : value) {
			if (!isalpha(c) && !isspace(c))
				return false;
		}

		return true;
	}
}