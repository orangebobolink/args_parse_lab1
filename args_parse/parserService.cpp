#include "parserService.hpp"
#include <string>

#include "args/arg.hpp"

namespace args_parse
{
	OperatorType isOperator(const std::string& str)
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
	types::Result<bool> checkIfFollowingArgvIsValue(const char* nextElement,
		const bool argAllowsUseValue)
	{
		bool nextArgIsNoteOperator = false;

		if (nextElement != NULL)
		{
			nextArgIsNoteOperator = isOperator(nextElement) == OperatorType::NOPE;
		}

		if (nextArgIsNoteOperator && !argAllowsUseValue)
		{
			return { types::ErrorCase("arg doesn't allow use value") };
		}

		const bool isNextElementValue = nextArgIsNoteOperator && argAllowsUseValue;

		return { isNextElementValue };
	}
	types::Result<int> itemConsistsOfArgumentAndValue(std::string& value,
		std::string& item,
		std::string& longArg,
		int index
	)
	{
		if (value != "")
		{
			return { {"Multiple value transmission"} };
		}

		value = item.substr(longArg.length());

		return { index };
	}
	bool checkItemConsistsOfArgumentAndValue(std::string& item, const std::string& longArg)
	{
		const size_t equalSignPosition = item.find(longArg);
		const bool theItemCheckConsistsOfAnArgumentAndAValue =
			equalSignPosition != std::string::npos
			&& equalSignPosition == 0
			&& longArg.length() < item.length();

		return theItemCheckConsistsOfAnArgumentAndAValue;
	}
	bool checkArgumentIsWrittenInIncompleteForm(const std::string& item, std::string& longArg)
	{
		const size_t equalSignPosition = longArg.find(item);
		const bool isArgumentWrittenInAnIncompleteForm =
			equalSignPosition != std::string::npos && equalSignPosition == 0
			&& longArg.length() > item.length()
			&& item.length() > 0;

		return isArgumentWrittenInAnIncompleteForm;
	}
	void checkItemForEqualSign(std::string& item, std::string& value)
	{
		const size_t equalSignPosition = item.find('=');

		if (equalSignPosition != std::string::npos) {
			value = item.substr(equalSignPosition + 1);
			item = item.substr(0, equalSignPosition);
		}
	}

	types::Result<bool> checkArgumentHasValue(args::Arg* foundOperator)
	{
		const bool argHaveToHaveValue = foundOperator->getCanHasValue() == true;
		const bool argHasValue = foundOperator->getHasValue() == true;

		if (argHaveToHaveValue && !argHasValue)
		{
			return { types::ErrorCase("Operator has to have a value") };
		}

		/*if (!argHaveToHaveValue && argHasValue)
		{
			return { types::ErrorCase("Operator has to have a value") };
		}*/

		return { true };
	}

	types::Result<bool> checkArgumentValidity(args::Arg* arg)
	{
		auto resultHasValue = checkArgumentHasValue(arg);
		if (!resultHasValue.isOk()) return resultHasValue;

		return { true };
	}
}
