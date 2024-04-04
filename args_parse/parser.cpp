#include <iostream>
#include "parser.hpp"
#include "vectorService.hpp"
#include "parserService.hpp"

namespace args_parse
{
	constexpr int StartingStringPosition = 0;

	Parser::Parser(int argc, const char** argv)
	{
		this->argc = argc;
		this->argv = argv;
	}

	types::Result<int> Parser::findLongOperator(std::string& item, std::string& value) const
	{
		int index = 0;
		for (auto& arg : this->args) {
			auto longArg = arg->getLongArg();

			if (longArg == item)
			{
				return { true, index };
			}

			/// Item состоит из аргумента (в полной форме) и его значения
			if (ParserService::checkItemConsistsOfArgumentAndValue(item, longArg))
			{
				return ParserService::itemConsistsOfArgumentAndValue(value, item, longArg, index);
			}

			/// Item состоит из аргумента написанного в неполной форме
			if (ParserService::checkArgumentIsWrittenInIncompleteForm(item, longArg))
			{
				return { true, index };
			}

			index++;
		}

		return { "operator is invalid" };
	}

	types::Result<bool> Parser::findShortOperator(std::string& item, std::string& value, std::vector<int>& indexVector) const
	{
		constexpr int LengthOfChar = 1;
		int index = 0;

		for (auto& arg : this->args) {
			const char shortArg = arg->getShortArg();
			const size_t pos = item.find(shortArg);

			/// Не аргумент
			if (pos != 0)
			{
				index++;
				continue;
			}

			/// Мы нашли аргумент, смотрим есть ли в item что-то ещё
			if (pos + LengthOfChar < item.length()) {
				item = item.substr(pos + LengthOfChar);

				/// Если аргумент принимает значение, то item - значение
				if (this->args[index]->getHasValue())
				{
					if (!item.empty())
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

	types::Result<std::vector<int>> Parser::getOperator(std::string& item, OperatorType operatorType) const
	{
		std::string value = "";
		ParserService::checkItemForEqualSign(item, value);

		std::vector<int> indexVector;

		if (operatorType == OperatorType::LONG)
		{
			constexpr int LengthOfTwoDash = 2;
			item = item.erase(StartingStringPosition, LengthOfTwoDash);

			auto result = findLongOperator(item, value);

			if (!result.success) return { result.error };

			const auto index = result.data;

			this->args[index]->setValue(value);
			indexVector.push_back(index);

			return { true, indexVector };
		}

		if (operatorType == OperatorType::SHORT)
		{
			constexpr int LengthOfOneDash = 1;
			item.erase(StartingStringPosition, LengthOfOneDash);

			auto result = findShortOperator(item, value, indexVector);

			if (!result.success) return { result.error };

			const auto indexOfLastArg = indexVector[0];

			this->args[indexOfLastArg]->setValue(value);

			return { true, indexVector };
		}

		return { "operator is invalid" };
	}

	types::Result<bool> Parser::parseNextElement(args::Arg* foundOperator, const char* nextElement, int& i) const
	{
		bool isNextElementValue = false;

		if (i + 1 < argc)
		{
			auto result = ParserService::checkIfFollowingArgvIsValue(nextElement,
				foundOperator->getHasValue());

			if (!result.success) return { result.error };

			isNextElementValue = result.data;
		}

		if (isNextElementValue)
		{
			if (!foundOperator->getValue().empty())
			{
				return { "Multiple value transmission" };
			}

			foundOperator->setValue(nextElement);

			i++;
		}

		return { true, true };
	}

	types::Result<bool> Parser::parse() const
	{
		std::vector<args::Arg*> vectorProcesses;

		for (int i = 1; i < argc; ++i)
		{
			const auto item = argv[i];
			std::string strItem(item);

			const auto operatorType = ParserService::isOperator(strItem);

			auto resultGetOperator = getOperator(strItem, operatorType);
			if (!resultGetOperator.success) return { resultGetOperator.error };

			auto indexVector = resultGetOperator.data;

			for (size_t i = 1; i < indexVector.size(); ++i) {
				args::Arg* foundOperator = this->args[indexVector[i]].get();

				auto resultArgumentValidity = ParserService::checkArgumentValidity(foundOperator);
				if (!resultArgumentValidity.success) return resultArgumentValidity;

				vectorProcesses.push_back(foundOperator);
			}

			const auto lastOperatorOfVector = this->args[indexVector[0]].get();
			const auto nextElement = argv[i + 1];

			auto resultParseNextElement = parseNextElement(lastOperatorOfVector, nextElement, i);
			if (!resultParseNextElement.success) return resultParseNextElement;

			auto resultArgumentValidity = ParserService::checkArgumentValidity(lastOperatorOfVector);
			if (!resultArgumentValidity.success) return resultArgumentValidity;

			vectorProcesses.push_back(lastOperatorOfVector);
		}

		auto result = invokeProcesses(vectorProcesses);

		return result;
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
