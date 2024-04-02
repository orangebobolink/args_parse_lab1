#include <iostream>
#include "parser.hpp"
#include "vectorService.hpp"

namespace args_parse
{
	const int StartingStringPosition = 0;

	Parser::Parser(int argc, const char** argv)
	{
		this->argc = argc;
		this->argv = argv;
	}

	OperatorType Parser::isOperator(const std::string str)
	{
		size_t pos = str.find("--");

		if (pos != std::string::npos && pos == StartingStringPosition) {
			return OperatorType::LONG;
		}

		pos = str.find("-");

		if (pos != std::string::npos && pos == StartingStringPosition) {
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
		for (auto& arg : this->args) {
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

	int Parser::getOperator(std::string item, OperatorType operatorType) const
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
			item = item.erase(StartingStringPosition, LENGTH_OF_TWO_DASH);

			auto index = findLongOperator(item, value);

			this->args[index]->setValue(value);

			
			return index;
		}

		if (operatorType == OperatorType::SHORT)
		{
			const int LENGTH_OF_ONE_DASH = 1;
			item.erase(StartingStringPosition, LENGTH_OF_ONE_DASH);

			auto index = findShortOperator(item, value);
			this->args[index]->setValue(value);

			return index;
		}

		throw std::invalid_argument("operator is invalid");
	}

	bool Parser::checkIfTheFollowingArgvIsAValue(const char* nextElement, const bool argAllowsUseValue)
	{
		bool nextArgIsNoteOperator = false;

		if (nextElement != NULL)
		{
			nextArgIsNoteOperator = isOperator(nextElement) == OperatorType::NOPE;
		}

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

			int index = getOperator(strItem, operatorType);

			auto foundOperator = this->args[index].get();

			auto nextElement = argv[i + 1];
			bool isNextElementValue = false;
			if (i + 1 < argc) 
			{
				isNextElementValue = checkIfTheFollowingArgvIsAValue(nextElement, foundOperator->getHasAValue());
			}

			if (isNextElementValue)
			{
				if (foundOperator->getValue() != "")
				{
					throw std::invalid_argument("Multiple value transmission");
				}

				foundOperator->setValue(nextElement);

				i++;
			}

			if (foundOperator->getHasAValue() == true && foundOperator->getValue() == "")
			{
				throw std::invalid_argument("Operator has to have a value");
			}

			if(foundOperator->getValue() != "" && !foundOperator->validateValue(foundOperator->getValue()))
			{
				throw std::invalid_argument("Invalid value");
			}

			vectorProcesses.push_back(foundOperator);
		}

		invokeProcesses(vectorProcesses);

		return true;
	}

	void Parser::addArg(std::unique_ptr<args::Arg> arg)
	{
		this->args.push_back(std::move(arg));
	}

	void Parser::addArgs(std::vector<std::unique_ptr<args::Arg>> args)
	{
		for(auto& arg : args)
		{
			addArg(std::move(arg));
		}
	}
}
