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
	Parser::~Parser()
	{
		this->args.clear();
	}

	OperatorType Parser::isOperator(string str)
	{
		size_t pos = str.find("--");

		if (pos != string::npos && pos == STARTING_STRING_POSITION) {
			return OperatorType::LONG;
		}

		pos = str.find("-");

		if (pos != string::npos && pos == STARTING_STRING_POSITION) {
			return OperatorType::SHORT;
		}

		return OperatorType::NOPE;
	}

	Arg Parser::findLongOperator(string item, string& value) const
	{
		for (auto arg : this->args) {
			auto longArg = arg.getLongArg();
			size_t equalSignPosition = item.find(longArg);

			if (equalSignPosition != string::npos && equalSignPosition == 0 && longArg.length() < item.length()) {
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

	Arg Parser::findShortOperator(string item, string& value) const
	{
		const int LENGHT_OF_CHAR = 1;
		for (auto arg : this->args) {
			size_t pos = item.find(arg.getShortArg());
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

	tuple<Arg, string> Parser::getOperator(string item, OperatorType operatorType) const
	{
		string value = "";
		size_t equalSignPosition = item.find('=');

		if (equalSignPosition != string::npos) {
			value = item.substr(equalSignPosition + 1);
			item = item.substr(0, equalSignPosition);
		}

		if (operatorType == OperatorType::LONG)
		{
			const int LENGTH_OF_TWO_DASH = 2;
			item = item.erase(STARTING_STRING_POSITION, LENGTH_OF_TWO_DASH);

			auto arg = findLongOperator(item, value);

			tuple<Arg, string> tuple = make_tuple(arg, value);

			return tuple;
		}

		if (operatorType == OperatorType::SHORT)
		{
			const int LENGTH_OF_ONE_DASH = 1;
			item.erase(STARTING_STRING_POSITION, LENGTH_OF_ONE_DASH);

			auto arg = findShortOperator(item, value);
			tuple<Arg, string> tuple = make_tuple(arg, value);

			return tuple;
		}

		throw std::invalid_argument("operator is invalid");
	}

	bool Parser::checkIfTheFollowingArgvIsAValue(const char* nextElement, Arg foundOperator)
	{
		bool nextArgIsNoteOperator = false;

		if (nextElement != NULL)
		{
			nextArgIsNoteOperator = isOperator(nextElement) == OperatorType::NOPE;
		}

		bool argAllowsUseValue = foundOperator.getAcceptingTheValue() != Status::FORBIDDEN;

		if (nextArgIsNoteOperator && !argAllowsUseValue)
		{
			throw std::invalid_argument("arg doesn't allow use value");
		}

		const bool isNextElementValue = nextArgIsNoteOperator && argAllowsUseValue;

		return isNextElementValue;
	}

	bool Parser::parse()
	{
		vector<tuple<Arg,string>> vectorProcesses;

		for (int i = 1; i < argc; ++i)
		{
			auto item = argv[i];
			std::string strItem(item);

			auto operatorType = isOperator(strItem);

			auto [foundOperator, value] = getOperator(strItem, operatorType);

			auto nextElement = argv[i + 1];
			bool isNextElementValue = checkIfTheFollowingArgvIsAValue(nextElement, foundOperator);

			if(isNextElementValue)
			{
				if (value != "")
				{
					throw std::invalid_argument("Multiple value transmission");
				}

				value = nextElement;

				i++;
			}

			tuple<Arg, string> tuple = make_tuple(foundOperator, value);
			vectorProcesses.push_back(tuple);
		}

		invokeProcesses(vectorProcesses);

		return true;
	}

	void Parser::addArg(Arg arg)
	{
		this->args.push_back(arg);
	}

	void Parser::addArgs(vector<Arg> args)
	{
		for(Arg arg:args)
		{
			addArg(arg);
		}
	}
}
