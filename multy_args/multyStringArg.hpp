#pragma once
#include <args/stringArg.hpp>
#include <locale>

namespace multy_args
{
	class MultyStringlArg : public args::StringArg
	{
	public:
		MultyStringlArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processWithValueFunction)(std::string value))
			: StringArg(shortArg, longArg, description, processWithValueFunction)
		{
			this->allowMultyValues = true;
		}
	};
}
