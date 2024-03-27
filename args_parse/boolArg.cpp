#include "arg.hpp"
#include <locale>
#include "validator.hpp"

namespace args_parse
{
	class BoolArg : public Arg, public IValidator
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


		bool IValidator::validateValue(string value) override
		{
			string lowerStr = "";

			for (auto elem : value)
				lowerStr += std::tolower(elem);

			return lowerStr == "true" || lowerStr == "false";
		}
	};
}
