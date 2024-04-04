#pragma once
#include <args/stringArg.hpp>
#include <locale>

namespace multy_args
{
	class MultyStringlArg : public args::StringArg
	{
	public:
		MultyStringlArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(),
			int maxUsageCount = 3)
			: StringArg(shortArg, longArg, description, process)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process() override;
	};
}
