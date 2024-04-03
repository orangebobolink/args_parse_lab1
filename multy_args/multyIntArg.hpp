#pragma once
#include <args/intArg.hpp>
#include <locale>

namespace multy_args
{
	class MultyIntArg : public args::IntArg
	{
	public:
		MultyIntArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processWithValueFunction)(std::string value))
			: IntArg(shortArg, longArg, description, processWithValueFunction)
		{
			this->allowMultyValues = true;
		}
	};
}
