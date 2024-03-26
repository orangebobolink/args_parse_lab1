#include <iostream>
#include "parser.hpp"

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

	Arg Parser::findLongOperator(string item, string& value)
	{
		for (auto arg : this->args) {
			size_t equalSignPosition = item.find(arg.getLongArg());

			if (equalSignPosition != string::npos && equalSignPosition == 0) {
				if (value != "")
				{
					throw std::invalid_argument("Multiple value transmission");
				}

				value = item.substr(arg.getLongArg().length());

				return arg;
			}

			if (arg.getLongArg() == item)
			{
				return arg;
			}
		}

		throw std::invalid_argument("operator is invalid");
	}

	Arg Parser::findShortOperator(string item, string& value)
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

	tuple<Arg, string> Parser::getOperator(string item, OperatorType operatorType)
	{

		string value = "";
		size_t equalSignPosition = item.find('=');

		if (equalSignPosition != string::npos) {
			value = item.substr(equalSignPosition + 1);
		}

		if (operatorType == OperatorType::LONG)
		{
			const int LENGTH_OF_TWO_DASH = 2;
			item.erase(STARTING_STRING_POSITION, LENGTH_OF_TWO_DASH);

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


	bool Parser::parse()
	{
		typedef void (*processes)();
		vector<processes> vectorProcesses;

		typedef void (*processesWithValue)(string);
		vector<processesWithValue> vectorProcessesWithValue;
		vector<string> values;

		for (int i = 1; i < argc; ++i)
		{
			auto item = argv[i];
			std::string strItem(item);

			auto operatorType = isOperator(strItem);

			auto [foundOperator, value] = getOperator(strItem, operatorType);

			bool nextArgIsNoteOperator = isOperator(argv[i + 1]) == OperatorType::NOPE;
			bool argAllowsUseValue = foundOperator.getAcceptingTheValue() != Status::FORBIDDEN;

			if (nextArgIsNoteOperator && argAllowsUseValue)
			{
				if (value != "")
				{
					throw std::invalid_argument("Multiple value transmission");
				}

				value = argv[i + 1];

				//foundOperator.processWithValue(value);

				vectorProcessesWithValue.push_back(*foundOperator.processWithValue);
				values.push_back(value);
			}
			else if (nextArgIsNoteOperator && !argAllowsUseValue)
			{
				throw std::invalid_argument("arg doesn't allow use value");
			}
			else
			{
				vectorProcesses.push_back(*foundOperator.process);

				//foundOperator.process();
			}
		}

		return true;
	}
	void Parser::addArg(Arg arg)
	{
		this->args.push_back(arg);
	}
}