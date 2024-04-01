#include <iostream>
#include "parser.hpp"
#include "vectorService.hpp"
#include <args/emptyArg.hpp>
#include <args/valueArg.hpp>

namespace args_parse
{
	const int STARTING_STRING_POSITION = 0;

	Parser::Parser(int argc, const char** argv)
	{
		this->argc = argc;
		this->argv = argv;
	}
	Parser::~Parser()
	{
		this->args.clear();
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

	args::Arg Parser::findLongOperator(std::string item, std::string& value) const
	{
		for (auto arg : this->args) {
			auto longArg = arg->getLongArg();
			const size_t equalSignPosition = item.find(longArg);

			if (equalSignPosition != std::string::npos && equalSignPosition == 0 && longArg.length() < item.length()) {
				if (value != "")
				{
					throw std::invalid_argument("Multiple value transmission");
				}

				value = item.substr(longArg.length());

				return arg;
			}

			if (longArg == item)
			{
				return arg;
			}
		}

		throw std::invalid_argument("operator is invalid");
	}

	args::Arg Parser::findShortOperator(std::string item, std::string& value) const
	{
		const int LENGHT_OF_CHAR = 1;
		for (auto& arg : this->args) {
			const size_t pos = item.find(arg->getShortArg());
			if (pos == 0) {
				if (pos + LENGHT_OF_CHAR < item.length()) {
					if (value != "")
					{
						throw std::invalid_argument("Multiple value transmission");
					}

					value = item.substr(pos + LENGHT_OF_CHAR);
				}

				return arg;
			}
		}

		throw std::invalid_argument("operator is invalid");
	}

	std::tuple<args::Arg, std::string> Parser::getOperator(std::string item, OperatorType operatorType) const
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

			auto arg = findLongOperator(item, value);

			std::tuple<args::Arg, std::string> tuple = make_tuple(arg, value);

			return tuple;
		}

		if (operatorType == OperatorType::SHORT)
		{
			const int LENGTH_OF_ONE_DASH = 1;
			item.erase(STARTING_STRING_POSITION, LENGTH_OF_ONE_DASH);

			auto arg = findShortOperator(item, value);
			std::tuple<args::Arg, std::string> tuple = make_tuple(arg, value);

			return tuple;
		}

		throw std::invalid_argument("operator is invalid");
	}

	bool Parser::checkIfTheFollowingArgvIsAValue(const char* nextElement, args::Arg foundOperator)
	{
		bool nextArgIsNoteOperator = false;

		if (nextElement != NULL)
		{
			nextArgIsNoteOperator = isOperator(nextElement) == OperatorType::NOPE;
		}

		//const bool argAllowsUseValue = foundOperator.getAcceptingTheValue() != args::Status::FORBIDDEN;
		const bool argAllowsUseValue = typeid(foundOperator).name() == "ValueType";

		if (nextArgIsNoteOperator && !argAllowsUseValue)
		{
			throw std::invalid_argument("arg doesn't allow use value");
		}

		const bool isNextElementValue = nextArgIsNoteOperator && argAllowsUseValue;

		return isNextElementValue;
	}

	bool Parser::parse()
	{
		std::vector<std::tuple<args::Arg, std::string>> vectorProcesses;

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

			std::tuple<args::Arg, std::string> tuple = make_tuple(foundOperator, value);
			vectorProcesses.push_back(tuple);
		}

		invokeProcesses(vectorProcesses);

		return true;
	}

	void Parser::addArg(std::unique_ptr<args::Arg> arg)
	{
		this->args.push_back(std::make_unique<args::Arg>(arg));
	}

	void Parser::addArgs(std::vector<std::unique_ptr<args::Arg>> args)
	{
		this->args = args;
	}
}
