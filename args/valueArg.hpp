#pragma once
#include "arg.hpp"

namespace args
{
	class ValueArg : public Arg
	{
	public:
		ValueArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processWithValueFunction)(std::string value))
			: Arg(shortArg, longArg, description, processWithValueFunction)
		{
			this->hasValue = true;
		}

		bool validateValue(std::string value) override;
	};
}
