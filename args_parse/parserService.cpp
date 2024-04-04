#include "parserService.hpp"
#include <string>

#include "args/arg.hpp"

namespace args_parse
{
	OperatorType ParserService::isOperator(const std::string& str)
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
	types::Result<bool> ParserService::checkIfFollowingArgvIsValue(const char* nextElement,
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
	types::Result<int> ParserService::itemConsistsOfArgumentAndValue(std::string& value,
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
	bool ParserService::checkItemConsistsOfArgumentAndValue(std::string& item, const std::string& longArg)
	{
		const size_t equalSignPosition = item.find(longArg);
		const bool theItemCheckConsistsOfAnArgumentAndAValue =
			equalSignPosition != std::string::npos
			&& equalSignPosition == 0
			&& longArg.length() < item.length();

		return theItemCheckConsistsOfAnArgumentAndAValue;
	}
	bool ParserService::checkArgumentIsWrittenInIncompleteForm(const std::string& item, std::string& longArg)
	{
		const size_t equalSignPosition = longArg.find(item);
		const bool isArgumentWrittenInAnIncompleteForm =
			equalSignPosition != std::string::npos && equalSignPosition == 0
			&& longArg.length() > item.length()
			&& item.length() > 0;

		return isArgumentWrittenInAnIncompleteForm;
	}
	void ParserService::checkItemForEqualSign(std::string& item, std::string& value)
	{
		const size_t equalSignPosition = item.find('=');

		if (equalSignPosition != std::string::npos) {
			value = item.substr(equalSignPosition + 1);
			item = item.substr(0, equalSignPosition);
		}
	}

	types::Result<bool> ParserService::checkArgumentHasValue(args::Arg* foundOperator)
	{
		const bool argHaveToHaveValue = foundOperator->getHasValue() == true;
		const bool argHasValue = foundOperator->getValue().empty();

		if (argHaveToHaveValue && argHasValue)
		{
			return { "Operator has to have a value" };
		}

		return { true, true };
	}

	types::Result<bool> ParserService::checkArgumentHasNotInvalidValue(args::Arg* foundOperator)
	{
		const auto valueIsNotEmpty = !foundOperator->getValue().empty();
		const auto valueDoesNotPassValidation = !foundOperator->validateValue(foundOperator->getValue());

		if (valueIsNotEmpty && valueDoesNotPassValidation)
		{
			return { "Invalid value" };

		}

		return { true, true };
	}

	types::Result<bool> ParserService::checkArgumentValidity(args::Arg* arg)
	{
		auto resultHasValue = checkArgumentHasValue(arg);
		if (!resultHasValue.success) return resultHasValue;

		auto resultHasNotInvalidValue = checkArgumentHasNotInvalidValue(arg);
		if (!resultHasNotInvalidValue.success) return resultHasNotInvalidValue;

		return { true, true };
	}
}
