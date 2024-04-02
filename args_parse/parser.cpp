#include <iostream>
#include "parser.hpp"
#include "vectorService.hpp"

namespace args_parse
{
	const int STARTING_STRING_POSITION = 0;

	Parser::Parser(int argc, const char** argv)
	{
		this->argc = argc;
		this->argv = argv;
	}

	OperatorType Parser::isOperator(const std::string str)
	{
		size_t pos = str.find("--");

		if (pos != std::string::npos && pos == STARTING_STRING_POSITION) {
			return OperatorType::LONG;
		}

		pos = str.find("-");

		if (pos != std::string::npos && pos == STARTING_STRING_POSITION) {
			return OperatorType::SHORT;
		}

		return OperatorType::NOPE;
	}

	int Parser::findLongOperator(std::string item, std::string& value) const
	{
		int index = 0;
		for (auto& arg : this->args) {
			auto longArg = arg->getLongArg();
			const size_t equalSignPosition = item.find(longArg);

			if (equalSignPosition != std::string::npos && equalSignPosition == 0 && longArg.length() < item.length()) {
				if (value != "")
				{
					throw std::invalid_argument("Multiple value transmission");
				}

				value = item.substr(longArg.length());

				return index;
			}

			if (longArg == item)
			{
				return index;
			}

			index++;
		}

		throw std::invalid_argument("operator is invalid");
	}

	int Parser::findShortOperator(std::string item, std::string& value) const
	{
		const int LENGHT_OF_CHAR = 1;
		int index = 0;
		for (auto arg : this->args) {
			char shortArg = arg->getShortArg();
			const size_t pos = item.find(shortArg);
			if (pos == 0) {
				if (pos + LENGHT_OF_CHAR < item.length()) {
					if (value != "")
					{
						throw std::invalid_argument("Multiple value transmission");
					}

					value = item.substr(pos + LENGHT_OF_CHAR);
				}

				return index;
			}
			index++;
		}

		throw std::invalid_argument("operator is invalid");
	}

	std::tuple<args::Arg*, std::string> Parser::getOperator(std::string item, OperatorType operatorType) const
	{
		std::string value = "";
		size_t equalSignPosition = item.find('=');

		if (equalSignPosition != std::string::npos) {
			value = item.substr(equalSignPosition + 1);
			item = item.substr(0, equalSignPosition);
		}

		if (operatorType == OperatorType::LONG)
		{
			const int LENGTH_OF_TWO_DASH = 2;
			item = item.erase(STARTING_STRING_POSITION, LENGTH_OF_TWO_DASH);

			auto index = findLongOperator(item, value);

			std::tuple<args::Arg*, std::string> tuple = make_tuple(args[index], value);
			
			return tuple;
		}

		if (operatorType == OperatorType::SHORT)
		{
			const int LENGTH_OF_ONE_DASH = 1;
			item.erase(STARTING_STRING_POSITION, LENGTH_OF_ONE_DASH);

			auto index = findShortOperator(item, value);
			std::tuple<args::Arg*, std::string> tuple = make_tuple(args[index], value);

			return tuple;
		}

		throw std::invalid_argument("operator is invalid");
	}

	bool Parser::checkIfTheFollowingArgvIsAValue(const char* nextElement, args::Arg* foundOperator)
	{
		bool nextArgIsNoteOperator = false;

		if (nextElement != NULL)
		{
			nextArgIsNoteOperator = isOperator(nextElement) == OperatorType::NOPE;
		}

		//const bool argAllowsUseValue = foundOperator.getAcceptingTheValue() != args::Status::FORBIDDEN;
		const bool argAllowsUseValue = foundOperator->getHasAValue() == true;

		if (nextArgIsNoteOperator && !argAllowsUseValue)
		{
			throw std::invalid_argument("arg doesn't allow use value");
		}

		const bool isNextElementValue = nextArgIsNoteOperator && argAllowsUseValue;

		return isNextElementValue;
	}

	bool Parser::parse()
	{
		std::vector<args::Arg*> vectorProcesses;

		for (int i = 1; i < argc; ++i)
		{
			auto item = argv[i];
			std::string strItem(item);

			auto operatorType = isOperator(strItem);

			auto [foundOperator, value] = getOperator(strItem, operatorType);

			auto nextElement = argv[i + 1];
			bool isNextElementValue = checkIfTheFollowingArgvIsAValue(nextElement, foundOperator);

			if (isNextElementValue)
			{
				if (value != "")
				{
					throw std::invalid_argument("Multiple value transmission");
				}

				value = nextElement;

				i++;
			}

			if (typeid(foundOperator).name() == "ValueType" && value == "")
			{
				throw std::invalid_argument("Operator has to have a value");
			}

			/*if(value != "" && validator->validateValue(value))
			{
				throw std::invalid_argument("Invalid value");
			}*/

			foundOperator->setValue(value);

			vectorProcesses.push_back(foundOperator);
		}

		invokeProcesses(vectorProcesses);

		return true;
	}

	void Parser::addArg(args::Arg* arg)
	{
		args.push_back(arg);
	}

	void Parser::addArgs(std::vector<args::Arg*> args)
	{
		for(auto arg : args)
		{
			addArg(arg);
		}
	}
}
