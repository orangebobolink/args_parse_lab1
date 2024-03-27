#include "arg.hpp"
#include "validator.hpp"

namespace args_parse
{
	class StringArg : public Arg, public IValidator
	{
	public:
		explicit StringArg(char shortArg = ' ',
			string longArg = "",
			string description = "",
			void (*processFunction)() = []() {},
			Status acceptingTheValue = Status::FORBIDDEN,
			void(*processWithValueFunction)(string value) = [](string value) {}) : Arg(shortArg, longArg, description,
				processFunction, acceptingTheValue, processWithValueFunction) { }

		explicit StringArg(char shortArg = ' ',
			string longArg = "s",
			string description = "",
			void(*processWithValueFunction)(string value) = [](string value) {}) : Arg(shortArg, longArg, description,
				[]() {}, Status::MUST_BE, processWithValueFunction) { }

		bool validateValue(string value) override
		{
			for (const char c : value) {
				if (!isalpha(c) && !isspace(c))
					return false;
			}

			return true;
		}
	};
}
