#include "arg.hpp"
#include <locale> 

namespace args_parse
{
	class BoolArg : public Arg
	{
	public:
		explicit BoolArg(char shortArg = ' ',
			string longArg = "",
			string description = "",
			void (*processFunction)() = []() {},
			Status acceptingTheValue = Status::FORBIDDEN,
			void(*processWithValueFunction)(string value) = [](string value) {}) : Arg(shortArg, longArg, description,
				processFunction, acceptingTheValue, processWithValueFunction) { }

		explicit BoolArg(char shortArg = ' ',
			string longArg = "",
			string description = "",
			void(*processWithValueFunction)(string value) = [](string value) {}) : Arg(shortArg, longArg, description,
				[]() {}, Status::MUST_BE, processWithValueFunction) { }


		bool validationValue(string value) override
		{
			string lowerStr = "";

			for (auto elem : value)
				lowerStr += std::tolower(elem);

			return lowerStr == "true" || lowerStr == "false";
		}
	};
}
