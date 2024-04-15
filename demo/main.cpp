#include <iomanip>
#include <args/arg.hpp>
#include <vector>
#include <memory>
#include <args_parse/parser.hpp>
#include <iostream>

#include "userDemoArg.hpp"

std::vector<std::unique_ptr<args::Arg>> getTestArgs();
args_parse::Parser getParser(const int argc, const char** argv);

/**
 * \brief Демо программы с использованием пользовательского типа
 * При успешной работе программы выводиться длинное имя аргументо и value если оно присуствиует 
 */
int main(int argc, const char** argv)
{
	auto parser = getParser(argc, argv);

	auto result = parser.parse();

	if (!result.isOk()) std::cout << result.error << std::endl;
}

args_parse::Parser getParser(const int argc, const char** argv)
{
	args_parse::Parser parser(argc, argv);
	auto args = std::move(getTestArgs());


	for (auto& arg : args)
	{
		parser.addArg(std::move(arg));
	}

	return parser;
}

auto stringValidator = args::Validator<std::string>();
auto intValidator = args::Validator<int>();
auto boolValidator = args::Validator<bool>();
auto ipValidator = IpValidator();

types::Result<bool> helpFunc(const args::Arg* arg, const args_parse::Parser* parser)
{
	auto args = parser->getArgs();

	for(auto& arg : args)
	{
		std::cout << "--" << arg->getLongArg() << std::setw(50) << arg->getDescription() << std::endl;
		std::cout << "-" << arg->getShortArg() << std::endl;
	}

	return { true };
}
types::Result<bool> defaultFunc(const args::Arg* arg, const args_parse::Parser* parser)
{
	std::cout << "--" << arg->getLongArg() << std::endl;
	return { true };
}

std::vector<std::unique_ptr<args::Arg>> getTestArgs()
{
	std::vector< std::unique_ptr<args::Arg>> args;

	args.push_back(std::make_unique<args::EmptyArg>('h', "help",
		"It's help operation",
		helpFunc));
	args.push_back(std::make_unique<args::MultyEmptyArg>('v', "version",
		"It's version operation",
		defaultFunc, 3));
	args.push_back(std::make_unique<args::ValueArg<std::string>>('o', "output",
		"It's output operation",
		defaultFunc, &stringValidator));
	args.push_back(std::make_unique<args::ValueArg<int>>('g', "giveMyAge",
		"It has to show my age",
		defaultFunc, &intValidator));
	args.push_back(std::make_unique<args::ValueArg<bool>>('i', "isMyProgramCool",
		"It has to show you the truth",
		defaultFunc, &boolValidator));
	args.push_back(std::make_unique<IpArg>('n', "network",
		"That's my ip",
		defaultFunc, &ipValidator));

	return args;
}