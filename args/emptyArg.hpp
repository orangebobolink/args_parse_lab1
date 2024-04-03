#pragma once
#include "arg.hpp"

namespace args
{
	class EmptyArg : public Arg
	{
	public:
		EmptyArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processFunction)())
			: Arg(shortArg, longArg, description, processFunction)
		{
			this->hasValue = false;
		}

		bool validateValue(std::string value) override;
	};
}
