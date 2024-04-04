#include "arg.hpp"
#include <stdexcept>

namespace args
{
	bool Arg::getHasValue() const
	{
		return hasValue;
	}

	void Arg::setValue(const std::string& value)
	{
		this->value = value;
	}

	std::string Arg::getValue() const
	{
		return value;
	}

	Arg::Arg(char shortArg,
	         std::string longArg,
	         std::string description,
	         types::Result<bool>(*processFunction)(),
	         types::Result<bool>(*processWithValueFunction)(std::string value))
		: description(description), shortArg(shortArg), longArg(longArg),
		processFunction(processFunction), processWithValueFunction(processWithValueFunction) {}

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
		return this->processFunction();
	}

	types::Result<bool> Arg::processWithValue(std::string value)
	{
		if (!hasValue) {
			return { "Argument does not expect a value." };
		}

		return this->processWithValueFunction(value);
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
}