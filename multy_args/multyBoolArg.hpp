#pragma once
#include <args/boolArg.hpp>
#include <locale>

namespace multy_args
{
	class MultyBoolArg : public args::BoolArg
	{
	public:
		MultyBoolArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processWithValueFunction)(std::string value),
			int maxUsageCount = 3)
			: BoolArg(shortArg, longArg, description, processWithValueFunction)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> processWithValue(std::string value) override;
	};
}
