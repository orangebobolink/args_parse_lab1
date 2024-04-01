#include "vectorService.hpp"

namespace args_parse
{
	void invokeProcesses(std::vector<std::tuple<args::Arg, std::string>> vector)
	{
		for (std::tuple<args::Arg, std::string> tuple : vector)
		{
			args::Arg arg = std::get<args::Arg>(tuple);
			std::string value = std::get<std::string>(tuple);

			if (value == "")
			{
				arg.process();
			}
			else
			{
				arg.processWithValue(value);
			}
		}
	}
}