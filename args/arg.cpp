#include "arg.hpp"
#include <stdexcept>
#include <iostream>

namespace args
{
	bool Arg::getHasValue() const
	{
		return this->hasValue;
	}

	int Arg::getMaxUsageCount() const
	{
		return this->maxUsageCount;
	}

	void Arg::setValue(const std::string& value)
	{
		this->value = value;
	}

	std::string Arg::getValue() const
	{
		return this->value;
	}

	Arg::Arg(char shortArg,
		std::string longArg,
		std::string description,
		types::Result<bool>(*processFunction)())
		: description(description), shortArg(shortArg), longArg(longArg),
		processFunction(processFunction) {}

	std::string Arg::getDescriptiong() const
	{
		return this->description;
	}

	void Arg::setDescription(std::string description)
	{
		this->description = description;
	}

	char Arg::getShortArg() const
	{
		return this->shortArg;
	}

	std::string Arg::getLongArg() const
	{
		return this->longArg;
	}

	types::Result<bool> Arg::process()
	{
		if (!this->hasValue && this->value != "")
		{
			return { std::string("Value is forbidden") };
		}

		return this->processFunction();
	}

	bool Arg::validateValue(std::string value)
	{
		return false;
	}

	void Arg::incrementUsageCount() {
		this->usageCount++;
	}

	void Arg::setUsageCount(int count) {
		this->usageCount = count;
	}

	int Arg::getUsageCount() const
	{
		return this->usageCount;
	}

	bool Arg::getAllowMultyValues() const
	{
		return this->allowMultyValues;
	}

	bool args::EmptyArg::validateValue(std::string value)
	{
		return true;
	}

	types::Result<bool> args::EmptyArg::process()
	{
		return this->args::Arg::process();
	}

	bool args::ValueArg::validateValue(std::string value)
	{
		return true;
	}

	types::Result<bool> args::ValueArg::process()
	{
		std::cout << this->getShortArg() << this->value << std::endl;
		return { true };
	}

	bool IntArg::validateValue(std::string value)
	{
		std::string::const_iterator it = value.begin();

		while (it != value.end() && std::isdigit(*it)) ++it;

		return !value.empty() && it == value.end();
	}

	bool StringArg::validateValue(std::string value)
	{
		for (const char c : value) {
			if (!isalpha(c) && !isspace(c))
				return false;
		}

		return true;
	}

	bool BoolArg::validateValue(std::string value)
	{
		std::string lowerStr = "";

		for (auto elem : value)
			lowerStr += std::tolower(elem);

		return lowerStr == "true" || lowerStr == "false";
	}

	types::Result<bool> args::MultyBoolArg::process()
	{
		std::cout << this->value << " " << this->usageCount << std::endl;
		return { true };
	}

	types::Result<bool> args::MultyEmptyArg::process()
	{
		std::cout << this->usageCount << std::endl;

		return args::EmptyArg::process();
	}

	types::Result<bool> args::MultyIntArg::process()
	{
		std::cout << this->value << " " << this->usageCount << std::endl;

		return { true };
	}

	types::Result<bool> args::MultyStringlArg::process()
	{
		std::cout << this->value << " " << this->usageCount << std::endl;

		return { true };
	}
}