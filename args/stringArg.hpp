#pragma once
#include "valueArg.hpp"

namespace args
{
	class StringArg : public ValueArg
	{
	public:
		StringArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)())
			: ValueArg(shortArg, longArg, description, process) {}

		bool validateValue(std::string value) override;
	};
}
