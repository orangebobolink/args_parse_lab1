#include "vectorService.hpp"
#include <memory>
#include <unordered_map>

namespace args_parse
{
	types::Result<bool> invokeProcesses(std::vector<args::Arg*> vector)
	{
		std::unordered_map<args::Arg*, int> typeCount;

		for (auto& arg : vector) {
			arg->incrementUsageCount();
			typeCount[arg]++;
		}

		for (auto& arg : typeCount)
		{
			if (arg.first->getUsageCount() > 1 && !arg.first->getAllowMultyValues())
			{
				return { "Forbiddent mylty arg for this argument" };
			}

			std::string value = arg.first->getValue();

			if (value == "")
			{
				auto result = arg.first->process();
				if (!result.success) return result;
			}
			else
			{
				auto result = arg.first->processWithValue(value);
				if (!result.success) return result;
			}
		}

		return { true, true };
	}
}