#pragma once
#include "valueArg.hpp"

namespace args
{
	class StringArg : public ValueArg
	{
	public:
		StringArg(char shortArg = ' ',
			std::string longArg = "",
			std::string description = "",
			void(*processWithValueFunction)(std::string value) = [](std::string value) {})
		: ValueArg(shortArg, longArg, description,processWithValueFunction) { }

		bool validateValue(std::string value) override;
	};
}
