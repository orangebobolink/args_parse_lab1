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
			types::Result<bool>(*process)())
			: Arg(shortArg, longArg, description, process)
		{
			this->hasValue = true;
		}

		bool validateValue(std::string value) override;
		types::Result<bool> process() override;
	};
}
