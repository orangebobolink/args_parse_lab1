#pragma once
#include <args/emptyArg.hpp>
#include <locale>

namespace multy_args
{
	class MultyEmptyArg : public args::EmptyArg
	{
	public:
		MultyEmptyArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processFunction)(),
			int maxUsageCount = 3)
			: EmptyArg(shortArg, longArg, description, processFunction)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process() override;
	};
}
