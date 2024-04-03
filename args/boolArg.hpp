#pragma once
#include <locale>

#include "valueArg.hpp"

namespace args
{
	class BoolArg : public ValueArg
	{
	public:
		BoolArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processWithValueFunction)(std::string value))
			: ValueArg(shortArg, longArg, description, processWithValueFunction) { }


		bool validateValue(std::string value) override;
	};
}
