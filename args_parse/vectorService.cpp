#include "vectorService.hpp"
#include <memory>
#include <unordered_map>
#include <iostream>

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
				return { std::string("Forbiddent mylty arg for this argument") };
			}

			if (arg.first->getAllowMultyValues()
				&& arg.first->getUsageCount() > arg.first->getMaxUsageCount())
			{
				return { std::string("Exceeded maximum allowed usage count for this argument") };
			}

			auto result = arg.first->process();

			if (!result.data.has_value()) return result;
		}

		return { true };
	}
}