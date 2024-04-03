#pragma once
#include "valueArg.hpp"

namespace args
{
	class IntArg : public ValueArg
	{
	public:
		IntArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processWithValueFunction)(std::string value))
			: ValueArg(shortArg, longArg, description, processWithValueFunction) { }


		bool validateValue(std::string value) override;
	};
}
