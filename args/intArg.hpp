#pragma once
#include "arg.hpp"

namespace args
{
	class IntArg : public Arg
	{
	public:
		explicit IntArg(char shortArg = ' ',
			std::string longArg = "",
			std::string description = "",
			void (*processFunction)() = []() {},
			Status acceptingTheValue = Status::FORBIDDEN,
			void(*processWithValueFunction)(std::string value) = [](std::string value) {}) : Arg(shortArg, longArg, description,
				processFunction, acceptingTheValue, processWithValueFunction) { }

		explicit IntArg(char shortArg = ' ',
			std::string longArg = "",
			std::string description = "",
			void(*processWithValueFunction)(std::string value) = [](std::string value) {}) : Arg(shortArg, longArg, description,
				[]() {}, Status::MUST_BE, processWithValueFunction) { }


		bool validateValue(std::string value) override;
	};
}
