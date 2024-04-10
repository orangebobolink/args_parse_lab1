#include "arg.hpp"
#include <stdexcept>
#include <iostream>

namespace args
{
	types::Result<bool> IntValidator::validate(std::string& value)
	{
		std::string::const_iterator it = value.begin();

		while (it != value.end() && std::isdigit(*it)) ++it;

		return { !value.empty() && it == value.end() };
	}

	types::Result<bool> BoolValidator::validate(std::string& value)
	{
		std::string lowerStr;

		for (const auto elem : value)
			lowerStr += std::tolower(elem);

		return{ lowerStr == "true" || lowerStr == "false" };
	}

	types::Result<bool> StringValidator::validate(std::string& value)
	{
		for (const char c : value) {
			if (!isalpha(c) && !isspace(c))
				return {false};
		}

		return { true };
	}

	bool Arg::getHasValue() const
	{
		return this->hasValue;
	}

	int Arg::getMaxUsageCount() const
	{
		return this->maxUsageCount;
	}

	Arg::Arg(char shortArg,
		std::string longArg,
		std::string description,
		types::Result<bool>(*process)(const Arg* arg, const args_parse::Parser* parser))
		: description(std::move(description)), shortArg(shortArg), longArg(std::move(longArg)),
		processFunction(processFunction) {}

	std::string Arg::getDescription() const
	{
		return this->description;
	}

	void Arg::setDescription(std::string& description)
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

	types::Result<bool> Arg::process(const args_parse::Parser* parser)
	{
		return this->processFunction(this, parser);
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

	template<typename T>
	types::Result<bool> ValueArg<T>::process(const args_parse::Parser* parser)
	{
		std::cout << this->getShortArg() << " " << this->value << std::endl;
		return { true };
	}

	template<typename T>
	types::Result<bool> MultyValueArg<T>::process(const args_parse::Parser* parser)
	{
		std::cout << this->value << " " << this->usageCount << std::endl;
		return { true };
	}

	template <typename T>
	types::Result<bool> ValueArg<T>::tryParse(std::string& value)
	{
		const types::Result<bool> result = this->validator.validate(value);
		if (!result.isOk()) return { {" "} };

		try
		{
			T convertedValue = static_cast<T>(std::stol(value)); 
			this->value = convertedValue;
			return { true };
		}
		catch (const std::invalid_argument&)
		{
			return { false };
		}
		catch (const std::out_of_range&)
		{
			return { false };
		}
	}

	types::Result<bool> EmptyArg::tryParse(std::string& value)
	{
		return { types::ErrorCase(" ") };
	}

	types::Result<bool> EmptyArg::process(const args_parse::Parser* parser)
	{
		return Arg::process(parser);
	}

	types::Result<bool> args::MultyEmptyArg::process(const args_parse::Parser* parser)
	{
		std::cout << this->usageCount << std::endl;

		return args::EmptyArg::process(parser);
	}
}