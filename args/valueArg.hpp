#pragma once
#include "arg.hpp"

namespace args
{
	class ValueArg : public Arg
	{
	public:
		ValueArg(char shortArg = ' ',
			std::string longArg = "",
			std::string description = "",
			void (*processWithValueFunction)(std::string value))
		: Arg(shortArg, longArg, description, processWithValueFunction) { }

		bool validateValue(std::string value) override;
	};
}
