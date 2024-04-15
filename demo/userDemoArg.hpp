#pragma once
#include <args/arg.hpp>

/**
 * \brief Пример создания пользовательского валидатора
 */
class IpValidator : public args::Validator<std::string>	
{
	types::Result<bool> validate(std::string& value) override;
};

/**
 * \brief Пример создания пользовательского класса аргументов
 */
class IpArg : public args::ValueArg<std::string>
{
public:
	IpArg(char shortArg,
		const std::string& longArg,
		const std::string& description,
		types::Result<bool>(*process)(const Arg* arg, const args_parse::Parser* parser),
		args::Validator<std::string>* validator)
		: ValueArg<std::string>(shortArg, longArg, description, process, validator)
		{}
};