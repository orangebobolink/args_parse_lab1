#include "arg.hpp"
#include <stdexcept>

namespace args 
{
	Arg::Arg(char shortArg,
		std::string longArg,
		std::string description,
		void (*processFunction)() ,
		Status acceptingTheValue,
		void(*processWithValueFunction)(std::string value))
	{
		this->longArg = longArg;
		this->shortArg = shortArg;
		this->description = description;
		this->processFunction = processFunction;
		this->acceptingTheValue = acceptingTheValue;
		this->processWithValueFunction = processWithValueFunction;
	}
	Arg::Arg(std::string longArg,
		std::string description,
		void (*processFunction)(),
		Status acceptingTheValue,
		void(*processWithValueFunction)(std::string value))
		: Arg(' ', longArg, description, processFunction, acceptingTheValue, processWithValueFunction)
	{
	}
	Arg::Arg(char shortArg, 
		std::string longArg,
		std::string description,
		void (*processFunction)())
		: Arg(shortArg, longArg, description, processFunction, Status::FORBIDDEN, [](std::string value){})
	{
	}

	Arg::Arg(char shortArg, 
		std::string longArg,
		std::string description,
		void(*processWithValueFunction)(std::string value))
		: Arg(' ', longArg, description, []() {}, Status::MUST_BE, processWithValueFunction)
	{
	}

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
	 
	Status Arg::getAcceptingTheValue() const
	{
		return this->acceptingTheValue;
	}

	void Arg::process()
	{
		this->processFunction();
	}

	void Arg::processWithValue(std::string value)
	{
		if (this->acceptingTheValue == Status::FORBIDDEN)
		{
			throw std::invalid_argument("value is forbbiden");
		}

		this->processWithValueFunction(value);
	}

	bool Arg::validateValue(std::string value)
	{
		return false;
	}
}