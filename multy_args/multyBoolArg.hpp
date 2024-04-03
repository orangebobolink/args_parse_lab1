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
			types::Result<bool>(*processWithValueFunction)(std::string value))
			: BoolArg(shortArg, longArg, description, processWithValueFunction)
		{
			this->allowMultyValues = true;
		}

		types::Result<bool> processWithValue(std::string value) override;
	};
}
