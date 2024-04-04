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
			types::Result<bool>(*process)(),
			int maxUsageCount = 3)
			: BoolArg(shortArg, longArg, description, process)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process() override;
	};
}
