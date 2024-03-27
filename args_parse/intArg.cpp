#include "arg.hpp"

namespace args_parse
{
	class IntArg : public Arg
	{
	public:
		explicit IntArg(char shortArg = ' ',
			string longArg = "",
			string description = "",
			void (*processFunction)() = []() {},
			Status acceptingTheValue = Status::FORBIDDEN,
			void(*processWithValueFunction)(string value) = [](string value) {}) : Arg(shortArg, longArg, description,
				processFunction, acceptingTheValue, processWithValueFunction) { }

		explicit IntArg(char shortArg = ' ',
			string longArg = "",
			string description = "",
			void(*processWithValueFunction)(string value) = [](string value) {}) : Arg(shortArg, longArg, description,
				[]() {}, Status::MUST_BE, processWithValueFunction) { }


		bool validationValue(string value) override
		{
			std::string::const_iterator it = value.begin();

			while (it != value.end() && std::isdigit(*it)) ++it;

			return !value.empty() && it == value.end();
		}
	};
}
