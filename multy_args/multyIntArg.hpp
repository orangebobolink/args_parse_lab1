#pragma once
#include <args/intArg.hpp>
#include <locale>

namespace multy_args
{
	class MultyIntArg : public args::IntArg
	{
	public:
		MultyIntArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(),
			int maxUsageCount = 3)
			: IntArg(shortArg, longArg, description, process)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process() override;
	};
}
