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

	std::vector<args::Arg*> Parser::getArgs() const
	{
		std::vector<args::Arg*> ptr_args;

		ptr_args.reserve(this->args.size());
		for(auto& arg : this->args)
		{
			ptr_args.push_back(arg.get());
		}

		return ptr_args;
	}

	types::Result<int> Parser::findLongOperator(std::string& item, std::string& value) const
	{
		int index = 0;
		for (auto& arg : this->args) {
			auto longArg = arg->getLongArg();

			if (longArg == item)
			{
				return { index };
			}

			/// Item состоит из аргумента (в полной форме) и его значения
			if (checkItemConsistsOfArgumentAndValue(item, longArg))
			{
				return itemConsistsOfArgumentAndValue(value, item, longArg, index);
			}

			/// Item состоит из аргумента написанного в неполной форме
			if (checkArgumentIsWrittenInIncompleteForm(item, longArg))
			{
				return { index };
			}

			index++;
		}

		return { types::ErrorCase("operator is invalid")};
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
				if (this->args[index]->getCanHasValue())
				{
					if (!item.empty())
					{
						value = item;

						indexVector.push_back(index);
						return { true };
					}

					return { types::ErrorCase("Multiple value transmission") };
				}

				/// Возможно это другой аргумент 
				auto result = findShortOperator(item, value, indexVector);

				if (!result.isOk() || !result.data.value()) return { result.error };
			}

			indexVector.push_back(index);

			return { true };
		}

		return { types::ErrorCase("operator is invalid") };
	}

	types::Result<std::vector<int>> Parser::getOperator(std::string& item, OperatorType operatorType) const
	{
		std::string value = "";
		checkItemForEqualSign(item, value);

		std::vector<int> indexVector;

		if (operatorType == OperatorType::LONG)
		{
			constexpr int LengthOfTwoDash = 2;
			item = item.erase(StartingStringPosition, LengthOfTwoDash);

			auto result = findLongOperator(item, value);

			if (!result.data.has_value()) return { result.error };

			const auto index = result.data.value();
			auto resultParse = this->args[index]->tryParse(value);
			if (!resultParse.data.value()) return { types::ErrorCase("something") };

			indexVector.push_back(index);

			return { indexVector };
		}

		if (operatorType == OperatorType::SHORT)
		{
			constexpr int LengthOfOneDash = 1;
			item.erase(StartingStringPosition, LengthOfOneDash);

			auto result = findShortOperator(item, value, indexVector);

			if (!result.isOk()) return { result.error };

			const auto indexOfLastArg = indexVector[0];
			auto resultParse = this->args[indexOfLastArg]->tryParse(value);
			if (!resultParse.data.value()) return { types::ErrorCase("something") };

			return { indexVector };
		}

		return { types::ErrorCase("operator is invalid")};
	}

	types::Result<bool> Parser::parseNextElement(args::Arg* foundOperator, const char* nextElement, int& i) const
	{
		bool isNextElementValue = false;

		if (i + 1 < argc)
		{
			auto result = checkIfFollowingArgvIsValue(nextElement,
				foundOperator->getCanHasValue());

			if (!result.isOk()) return { result.error };

			isNextElementValue = result.data.value();
		}

		if (isNextElementValue)
		{
			auto stringNextItem = std::string(nextElement);
			auto result = foundOperator->tryParse(stringNextItem);

			if (!result.isOk())
				return { types::ErrorCase("Invalid") };
			
			i++;
		}

		return { true };
	}

	types::Result<bool> Parser::parse() const
	{
		std::vector<args::Arg*> vectorProcesses;

		for (int i = 1; i < argc; ++i)
		{
			const auto item = argv[i];
			std::string strItem(item);

			const auto operatorType = isOperator(strItem);

			auto resultGetOperator = getOperator(strItem, operatorType);
			if (!resultGetOperator.isOk()) return { resultGetOperator.error };

			auto indexVector = resultGetOperator.data.value();

			for (size_t i = 1; i < indexVector.size(); ++i) {
				args::Arg* foundOperator = this->args[indexVector[i]].get();

				auto resultArgumentValidity = checkArgumentValidity(foundOperator);
				if (!resultArgumentValidity.isOk()) return resultArgumentValidity;

				vectorProcesses.push_back(foundOperator);
			}

			const auto lastOperatorOfVector = this->args[indexVector[0]].get();
			const auto nextElement = argv[i + 1];

			auto resultParseNextElement = parseNextElement(lastOperatorOfVector, nextElement, i);
			if (!resultParseNextElement.isOk()) return resultParseNextElement;

			auto resultArgumentValidity = checkArgumentValidity(lastOperatorOfVector);
			if (!resultArgumentValidity.isOk()) return resultArgumentValidity;

			vectorProcesses.push_back(lastOperatorOfVector);
		}

		auto result = invokeProcesses(vectorProcesses, this);

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
