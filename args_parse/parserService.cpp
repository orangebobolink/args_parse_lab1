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
	types::Result<int> ParserService::itemConsistsOfAnArgumentAndAValue(std::string& value,
		std::string& item,
		std::string& longArg,
		int index
	)
	{
		if (value != "")
		{
			return { "Multiple value transmission" };
		}

		value = item.substr(longArg.length());

		return { true, index };
	}
	bool ParserService::checkItemConsistsOfAnArgumentAndAValue(std::string& item, std::string& longArg)
	{
		const size_t equalSignPosition = item.find(longArg);
		bool theItemCheckConsistsOfAnArgumentAndAValue =
			equalSignPosition != std::string::npos
			&& equalSignPosition == 0
			&& longArg.length() < item.length();

		return theItemCheckConsistsOfAnArgumentAndAValue;
	}
	bool ParserService::checkArgumentIsWrittenInAnIncompleteForm(std::string& item, std::string& longArg)
	{
		const size_t equalSignPosition = longArg.find(item);
		bool isArgumentWrittenInAnIncompleteForm =
			equalSignPosition != std::string::npos && equalSignPosition == 0
			&& longArg.length() > item.length()
			&& item.length() > 0;

		return isArgumentWrittenInAnIncompleteForm;
	}
	void ParserService::checkTheItemCheckContainsAnEqualSign(std::string& item, std::string& value)
	{
		size_t equalSignPosition = item.find('=');

		if (equalSignPosition != std::string::npos) {
			value = item.substr(equalSignPosition + 1);
			item = item.substr(0, equalSignPosition);
		}
	}
}