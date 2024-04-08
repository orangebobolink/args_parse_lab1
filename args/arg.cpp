#include "arg.hpp"
#include <stdexcept>

namespace args
{
	template<typename T>
	bool Arg<T>::getHasValue() const
	{
		return hasValue;
	}

	template<typename T>
	void Arg<T>::setValue(T value)
	{
		this->value = value;
	}

	template<typename T>
	T Arg<T>::getValue() const
	{
		return value;
	}

	template<typename T>
	Arg<T>::Arg(char shortArg,
		std::string longArg,
		std::string description,
		const std::function<types::Result<bool>(args_parse::Parser* parser, Arg*)> process)
		: description(description), shortArg(shortArg), longArg(longArg),
		processArg(process) {}

	template<typename T>
	std::string Arg<T>::getDescriptiong() const
	{
		return this->description;
	}

	template<typename T>
	void Arg<T>::setDescription(std::string description)
	{
		this->description = description;
	}

	template<typename T>
	char Arg<T>::getShortArg() const
	{
		return this->shortArg;
	}

	template<typename T>
	std::string Arg<T>::getLongArg() const
	{
		return this->longArg;
	}

	template<typename T>
	types::Result<bool> Arg<T>::process(args_parse::Parser* parser)
	{
		if (!hasValue && value != "")
		{
			return { "Value is forbidden" };
		}

		return this->processArg(parser, this);
	}

	template<typename T>
	bool Arg<T>::validateValue(std::string value)
	{
		return false;
	}

	 
}