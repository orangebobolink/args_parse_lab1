#include <iostream>
#include "parser.hpp"
#include "vectorService.hpp"
#include "parserService.hpp"

namespace args_parse
{
	const int StartingStringPosition = 0;

	Parser::Parser(int argc, const char** argv)
	{
		this->argc = argc;
		this->argv = argv;
	}

	types::Result<int> Parser::findLongOperator(std::string item, std::string& value) const
	{
		int index = 0;
		for (auto& arg : this->args) {
			auto longArg = arg->getLongArg();

			if (longArg == item)
			{
				return { true, index };
			}

			/// Item состоит из аргумента (в полной форме) и его значения
			bool theItemCheckConsistsOfAnArgumentAndAValue =
				ParserService::checkItemConsistsOfAnArgumentAndAValue(item, longArg);

			if (theItemCheckConsistsOfAnArgumentAndAValue)
			{
				return ParserService::itemConsistsOfAnArgumentAndAValue(value, item, longArg, index);
			}

			/// Item состоит из аргумента написанного в неполной форме
			bool isArgumentWrittenInAnIncompleteForm =
				ParserService::checkArgumentIsWrittenInAnIncompleteForm(item, longArg);

			if (isArgumentWrittenInAnIncompleteForm)
			{
				return { true, index };
			}

			index++;
		}

		return { "operator is invalid" };
	}

	types::Result<bool> Parser::findShortOperator(std::string item, std::string& value, std::vector<int>& indexVector) const
	{
		const int LenghtOfChar = 1;
		int index = 0;
		for (auto& arg : this->args) {
			char shortArg = arg->getShortArg();
			const size_t pos = item.find(shortArg);

			/// Не аргумент
			if (pos != 0)
			{
				index++;
				continue;
			}

			/// Мы нашли аргумент, смотрим есть ли в item что-то ещё
			if (pos + LenghtOfChar < item.length()) {
				item = item.substr(pos + LenghtOfChar);

				/// Если аргумент принимает значение, то item - значение
				if (this->args[index]->getHasAValue())
				{
					if (item != "")
					{
						value = item;

						indexVector.push_back(index);
						return { true, true };
					}

					return { "Multiple value transmission" };
				}

				/// Возможно это другой аргумент 
				auto result = findShortOperator(item, value, indexVector);

				if (!result.success) return { result.error };
			}

			indexVector.push_back(index);

			return { true,true };
		}

		return { "operator is invalid" };
	}

	types::Result<std::vector<int>> Parser::getOperator(std::string item, OperatorType operatorType) const
	{
		std::string value = "";
		ParserService::checkTheItemCheckContainsAnEqualSign(item, value);

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

	types::Result<bool> Parser::parse()
	{
		std::vector<args::Arg*> vectorProcesses;

		for (int i = 1; i < argc; ++i)
		{
			auto item = argv[i];
			std::string strItem(item);

			auto operatorType = ParserService::isOperator(strItem);

			auto getOperatorResult = getOperator(strItem, operatorType);

			if (!getOperatorResult.success) return { getOperatorResult.error };

			auto indexVector = getOperatorResult.data;

			for (size_t i = 1; i < indexVector.size(); ++i) {
				args::Arg* foundOperator = this->args[indexVector[i]].get();
				vectorProcesses.push_back(foundOperator);
			}

			args::Arg* foundOperator = this->args[indexVector[0]].get();

			auto nextElement = argv[i + 1];
			bool isNextElementValue = false;
			if (i + 1 < argc)
			{
				auto result = ParserService::checkIfTheFollowingArgvIsAValue(nextElement,
					foundOperator->getHasAValue());

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
