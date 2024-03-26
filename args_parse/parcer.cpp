#include "parcer.hpp"
#include <iostream>

namespace args_parse
{
	const int STARTING_STRING_POSITION = 0;

	Parcer::Parcer(int argc, const char** argv)
	{
		this->argc = argc;
		this->argv = argv;
	}
	Parcer::~Parcer()
	{
		this->args.clear();
	}

	OperatorType Parcer::isOperator(string str)
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

	Arg Parcer::findLongOperator(string item)
	{
		for (auto arg : this->args) {

			if (arg.getLongArg() == item)
			{
				return arg;
			}
		}

		throw std::invalid_argument("operator is invalid");
	}

	Arg Parcer::findShortOperator(char item)
	{
		for (auto arg : this->args) {

			if (arg.getShortArg() == (char)item)
			{
				return arg;
			}
		}

		throw std::invalid_argument("operator is invalid");
	}

	Arg Parcer::getOperator(string item, OperatorType operatorType)
	{
		if (operatorType == OperatorType::LONG)
		{
			const int LENGHT_OF_TWO_DASH = 2;
			item.erase(STARTING_STRING_POSITION, LENGHT_OF_TWO_DASH);
			return findLongOperator(item);
		}

		if (operatorType == OperatorType::SHORT)
		{
			const int LENGHT_OF_ONE_DASH = 1;
			auto charItem = item[LENGHT_OF_ONE_DASH];

			return findShortOperator(charItem);
		}

		throw std::invalid_argument("operator is invalid");
	}


	bool Parcer::parce()
	{
		const int LENGHT = argc;
		void (*processes)();
		void (*processesWithValue[LENGHT])(string);
		string values[LENGHT];

		for (int i = 1; i < argc; ++i)
		{
			auto item = argv[i];
			std::string strItem(item);

			auto operatorType = isOperator(strItem);

			Arg foundOperator = getOperator(strItem, operatorType);

			bool nextArgIsNoteOperator = isOperator(argv[i + 1]) == OperatorType::NOPE;
			bool argAllowsUseValue = foundOperator.getAcceptingTheValue() != Status::FORBIDDEN;

			if(nextArgIsNoteOperator && argAllowsUseValue)
			{
				string value(argv[i + 1]);
				 
				//foundOperator.processWithValue(value);
				unsigned length = std::size(processesWithValue);
				processesWithValue[length - 1] = *foundOperator.processWithValue;
				values[length - 1] = value;
			}
			else if(nextArgIsNoteOperator && !argAllowsUseValue)
			{
				throw std::invalid_argument("arg doesn't allow use value");
			}
			else
			{
				unsigned length = std::size(processes);
				processes[length - 1] = *foundOperator.process;
 
				//foundOperator.process();
			}
		}

		return true;
	}
	void Parcer::addArg(Arg arg)
	{
		this->args.push_back(arg);
	}
}