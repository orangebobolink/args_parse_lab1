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
			types::Result<bool>(*process)())
			: ValueArg(shortArg, longArg, description, process) {}


		bool validateValue(std::string value) override;
	};
}
