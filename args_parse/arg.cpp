#include "arg.hpp"
#include <stdexcept>

namespace args_parse
{
	bool Arg::validationValue(string value)
	{
		return false;
	}
	Arg::Arg(char shortArg,
		string longArg,
		string description,
		void (*processFunction)() ,
		Status acceptingTheValue,
		void(*processWithValueFunction)(string value))
	{
		this->longArg = longArg;
		this->shortArg = shortArg;
		this->description = description;
		this->processFunction = processFunction;
		this->acceptingTheValue = acceptingTheValue;
		this->processWithValueFunction = processWithValueFunction;
	}
	Arg::Arg( string longArg,
		string description,
		void (*processFunction)(),
		Status acceptingTheValue,
		void(*processWithValueFunction)(string value))
		: Arg(' ', longArg, description, processFunction, acceptingTheValue, processWithValueFunction)
	{
	}
	Arg::Arg(char shortArg, 
		string longArg,
		string description,
		void (*processFunction)())
		: Arg(shortArg, longArg, description, processFunction, Status::FORBIDDEN, [](string value){})
	{
	}

	Arg::Arg(char shortArg, 
		string longArg,
		string description,
		void(*processWithValueFunction)(string value))
		: Arg(' ', longArg, description, []() {}, Status::MUST_BE, processWithValueFunction)
	{
	}

	Arg::~Arg()
	{
		this->longArg.clear();
	}

	string Arg::getDescriptiong()
	{
		return this->description;
	}

	void Arg::setDescription(string description)
	{
		this->description = description;
	}

	char Arg::getShortArg()
	{
		return this->shortArg;
	}

	string Arg::getLongArg()
	{
		return this->longArg;
	}

	Status Arg::getAcceptingTheValue()
	{
		return this->acceptingTheValue;
	}

	void Arg::process()
	{
		this->processFunction();
	}

	void Arg::processWithValue(string value)
	{
		if (this->acceptingTheValue == Status::FORBIDDEN)
		{
			throw std::invalid_argument("value is forbbiden");
		}
		if (validationValue(value))
		{
			throw std::invalid_argument("value is invalid");
		}

		this->processWithValueFunction(value);
	}
}