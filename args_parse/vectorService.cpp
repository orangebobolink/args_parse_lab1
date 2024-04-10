#include "vectorService.hpp"
#include <unordered_map>

namespace args_parse
{
	types::Result<bool> invokeProcesses(std::vector<args::Arg*> vector, const args_parse::Parser* parser)
	{
		std::unordered_map<args::Arg*, int> typeCount;

		for (auto& arg : vector) {

			typeCount[arg]++;
		}

		for (auto& arg : typeCount)
		{
			/*if (arg.first->getUsageCount() > 1 && !arg.first->getAllowMultyValues())
			{
				return { std::string("Forbiddent mylty arg for this argument") };
			}

			if (arg.first->getAllowMultyValues()
				&& arg.first->getUsageCount() > arg.first->getMaxUsageCount())
			{
				return { std::string("Exceeded maximum allowed usage count for this argument") };
			}*/

			auto result = arg.first->process(parser);

			if (!result.data.has_value()) return result;
		}

		return { true };
	}
}