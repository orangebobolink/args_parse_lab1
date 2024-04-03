#include "vectorService.hpp"
#include <memory>

namespace args_parse
{
	types::Result<bool> invokeProcesses(std::vector<args::Arg*> vector)
	{
		for (auto& arg : vector)
		{
			std::string value = arg->getValue();

			if (value == "")
			{
				auto result = arg->process();
				if (!result.success) return result;
			}
			else
			{
				auto result = arg->processWithValue(value);
				if (!result.success) return result;
			}
		}

		return { true, true };
	}
}