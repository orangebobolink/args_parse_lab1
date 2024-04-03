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

	types::Result<int> Parser::findLongOperator(std::string item, std::string& value) const
	{
		int index = 0;
		for (auto& arg : this->args) {
			auto longArg = arg->getLongArg();
			const size_t equalSignPosition = item.find(longArg);

			/// вынести
			if (equalSignPosition != std::string::npos && equalSignPosition == 0 && longArg.length() < item.length()) {
				if (value != "")
				{
					return { "Multiple value transmission" };
				}

				value = item.substr(longArg.length());

				return { true, index };
			}

			const size_t equalSignPositions = longArg.find(item);

			if (equalSignPositions != std::string::npos && equalSignPositions == 0
				&& longArg.length() > item.length()
				&& item.length() > 0) {

				return { true, index };
			}

			if (longArg == item)
			{
				return { true, index };
			}

			index++;
		}
		return { "operator is invalid" };
	}

	types::Result<bool> Parser::findShortOperator(std::string item, std::string& value, std::vector<int>& indexVector) const
	{
		const int LENGHT_OF_CHAR = 1;
		int index = 0;
		for (auto& arg : this->args) {
			char shortArg = arg->getShortArg();
			const size_t pos = item.find(shortArg);
			if (pos == 0) {
				if (pos + LENGHT_OF_CHAR < item.length()) {
					//if (value != "")
					//{
					//	throw std::invalid_argument("Multiple value transmission");
					//}

					item = item.substr(pos + LENGHT_OF_CHAR);

					if (this->args[index]->getHasAValue())
					{
						if (item != "")
						{
							value = item;
							//this->args[index]->setValue(item);

							indexVector.push_back(index);
							return { true, true };
						}

						return { "Multiple value transmission" };
					}

					auto result = findShortOperator(item, value, indexVector);

					if (!result.success) return { result.error };

					//value = item.substr(pos + LENGHT_OF_CHAR);
				}

				indexVector.push_back(index);
				return { true,true };
			}

			index++;
		}

		return { "operator is invalid" };
	}

	types::Result<std::vector<int>> Parser::getOperator(std::string item, OperatorType operatorType) const
	{
		std::string value = "";
		size_t equalSignPosition = item.find('=');

		if (equalSignPosition != std::string::npos) {
			value = item.substr(equalSignPosition + 1);
			item = item.substr(0, equalSignPosition);
		}

		std::vector<int> indexVector;

		if (operatorType == OperatorType::LONG)
		{
			const int LENGTH_OF_TWO_DASH = 2;
			item = item.erase(StartingStringPosition, LENGTH_OF_TWO_DASH);


			auto result = findLongOperator(item, value);

			if (!result.success) return { result.error };

			auto index = result.data;

			this->args[index]->setValue(value);
			indexVector.push_back(index);

			return { true, indexVector };
		}

		if (operatorType == OperatorType::SHORT)
		{
			const int LENGTH_OF_ONE_DASH = 1;
			item.erase(StartingStringPosition, LENGTH_OF_ONE_DASH);


			auto result = findShortOperator(item, value, indexVector);

			if (!result.success) return { result.error };

			auto indexOfLastArg = indexVector[0];

			this->args[indexOfLastArg]->setValue(value);

			return { true, indexVector };
		}

		return { "operator is invalid" };
	}

	types::Result<bool> Parser::checkIfTheFollowingArgvIsAValue(const char* nextElement, const bool argAllowsUseValue)
	{
		bool nextArgIsNoteOperator = false;

		if (nextElement != NULL)
		{
			nextArgIsNoteOperator = isOperator(nextElement) == OperatorType::NOPE;
		}

		if (nextArgIsNoteOperator && !argAllowsUseValue)
		{
			return { "arg doesn't allow use value" };
		}

		const bool isNextElementValue = nextArgIsNoteOperator && argAllowsUseValue;

		return { true, isNextElementValue };
	}

	types::Result<bool> Parser::parse()
	{
		std::vector<args::Arg*> vectorProcesses;

		for (int i = 1; i < argc; ++i)
		{
			auto item = argv[i];
			std::string strItem(item);

			auto operatorType = isOperator(strItem);

			auto getOperatorResult = getOperator(strItem, operatorType);

			if (!getOperatorResult.success) return { getOperatorResult.error };

			auto indexVector = getOperatorResult.data;

			for (size_t i = 1; i < indexVector.size(); ++i) {
				auto foundOperator = this->args[indexVector[i]].get();
				vectorProcesses.push_back(foundOperator);
			}

			auto foundOperator = this->args[indexVector[0]].get();

			auto nextElement = argv[i + 1];
			bool isNextElementValue = false;
			if (i + 1 < argc)
			{
				auto result = checkIfTheFollowingArgvIsAValue(nextElement, foundOperator->getHasAValue());

				if (!result.success) return { result.error };

				isNextElementValue = result.data;
			}

			if (isNextElementValue)
			{
				if (foundOperator->getValue() != "")
				{
					return { "Multiple value transmission" };
				}

				foundOperator->setValue(nextElement);

				i++;
			}

			if (foundOperator->getHasAValue() == true && foundOperator->getValue() == "")
			{
				return { "Operator has to have a value" };
			}

			if (foundOperator->getValue() != "" && !foundOperator->validateValue(foundOperator->getValue()))
			{
				return { "Invalid value" };

			}

			vectorProcesses.push_back(foundOperator);
		}

		invokeProcesses(vectorProcesses);

		return { true, true };
	}

	void Parser::addArg(std::unique_ptr<args::Arg> arg)
	{
		this->args.push_back(std::move(arg));
	}

	void Parser::addArgs(std::vector<std::unique_ptr<args::Arg>> args)
	{
		for (auto& arg : args)
		{
			addArg(std::move(arg));
		}
	}
}
