#include "vectorService.hpp"
#include <memory>

namespace args_parse
{
	void invokeProcesses(std::vector<std::unique_ptr<args::Arg>> vector)
	{
		for (auto& arg : vector)
		{
			std::string value = arg->getValue();

			if (value == "")
			{
				arg->process();
			}
			else
			{
				arg->processWithValue(value);
			}
		}
	}
}