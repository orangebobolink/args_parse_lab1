#include "arg.hpp"
#include <stdexcept>

namespace args
{

	Arg::Arg(char shortArg,
		std::string longArg,
		std::string description,
		void(*processFunction)(),
		void(*processWithValueFunction)(std::string value))
	{
		this->longArg = longArg;
		this->shortArg = shortArg;
		this->description = description;
		this->processFunction = processFunction;
		this->processWithValueFunction = processWithValueFunction;
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

	void Arg::process()
	{
		this->processFunction();
	}

	void Arg::processWithValue(std::string value)
	{
		/*if (this->acceptingTheValue == Status::FORBIDDEN)
		{
			throw std::invalid_argument("value is forbbiden");
		}*/

		this->processWithValueFunction(value);
	}

	bool Arg::validateValue(std::string value)
	{
		return false;
	}
}