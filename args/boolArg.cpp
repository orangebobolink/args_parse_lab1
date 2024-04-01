#include "boolArg.hpp"
#include <locale>

namespace args
{
	bool BoolArg::validateValue(std::string value)
	{
		std::string lowerStr = "";

		for (auto elem : value)
			lowerStr += std::tolower(elem);

		return lowerStr == "true" || lowerStr == "false";
	}
}
