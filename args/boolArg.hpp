#pragma once
#include "arg.hpp"
#include <locale>

namespace args
{
	class BoolArg : public Arg
	{
	public:
		explicit BoolArg(char shortArg = ' ',
			std::string longArg = "",
			std::string description = "",
			void (*processFunction)() = []() {},
			Status acceptingTheValue = Status::FORBIDDEN,
			void(*processWithValueFunction)(std::string value) = [](std::string value) {}) : Arg(shortArg, longArg, description,
				processFunction, acceptingTheValue, processWithValueFunction) { }

		explicit BoolArg(char shortArg = ' ',
			std::string longArg = "",
			std::string description = "",
			void(*processWithValueFunction)(std::string value) = [](std::string value) {}) : Arg(shortArg, longArg, description,
				[]() {}, Status::MUST_BE, processWithValueFunction) { }


		bool validateValue(std::string value) override;
	};
}
