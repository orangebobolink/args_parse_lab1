#include "arg.hpp"

namespace args_parse
{
	class StringArg : public Arg
	{
	public:
		explicit StringArg(char shortArg = ' ',
			string longArg = "s",
			string description = "",
			void (*processFunction)() = []() {},
			Status acceptingTheValue = Status::FORBIDDEN,
			void(*processWithValueFunction)(string value) = [](string value) {}) : Arg(shortArg, longArg, description,
				processFunction, acceptingTheValue, processWithValueFunction) { }

		bool validationValue(string value) override
		{
			for (const char c : value) {
				if (!isalpha(c) && !isspace(c))
					return false;
			}

			return true;
		}
	};
}
