#include "parserService.hpp"
#include <string>
namespace args_parse
{
	OperatorType ParserService::isOperator(const std::string str)
	{
		if (str.size() >= 2
			&& str[0] == '-'
			&& str[1] == '-') {
			return OperatorType::LONG;
		}
		else if (!str.empty()
			&& str[0] == '-') {
			return OperatorType::SHORT;
		}

		return OperatorType::NOPE;
	}
	types::Result<bool> ParserService::checkIfTheFollowingArgvIsAValue(const char* nextElement,
		const bool argAllowsUseValue)
	{
		bool nextArgIsNoteOperator = false;

		if (nextElement != NULL)
		{
			nextArgIsNoteOperator = ParserService::isOperator(nextElement) == OperatorType::NOPE;
		}

		if (nextArgIsNoteOperator && !argAllowsUseValue)
		{
			return { "arg doesn't allow use value" };
		}

		const bool isNextElementValue = nextArgIsNoteOperator && argAllowsUseValue;

		return { true, isNextElementValue };
	}
}