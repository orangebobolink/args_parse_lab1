#include <iostream>
#include <args/arg.hpp>
#include <args/boolArg.hpp>
#include <args/intArg.hpp>
#include <args/stringArg.hpp>
#include <args/emptyArg.hpp>
#include <vector>

#include "args_parse/parser.hpp"

using namespace args;

std::vector<std::unique_ptr<Arg>> getTestArgs();

int main(int argc, const char** argv)
{
	auto args = getTestArgs();

	args_parse::Parser parcer(argc, argv);
	parcer.addArgs(std::move(args));

	try
	{
		parcer.parse();
	}
	catch (const std::invalid_argument& err)
	{
		std::cout << err.what() << std::endl;
	}
}

std::vector<std::unique_ptr<Arg>> getTestArgs()
{
	EmptyArg help('h', "help",
		"It's help operation",
		[]()
		{
			std::cout << "Something" << std::endl;
		});

	StringArg output('o', "output",
		"It's output operation",
		[](std::string value)
		{
			std::cout << value << std::endl;
		});

	IntArg giveMyAge('g', "giveMyAge",
		"It has to show my age",
		[](std::string value)
		{
			std::cout << value << std::endl;
		});

	BoolArg isMyProgramCool('i', "isMyProgramCool",
		"It has to show you the truth",
		[](std::string value)
		{
			std::cout << value << std::endl;
		});

	std::vector<std::unique_ptr<Arg>> args;

	args.push_back(std::make_unique<args::EmptyArg>(help));
	args.push_back(std::make_unique<args::StringArg>(output));
	args.push_back(std::make_unique<args::IntArg>(giveMyAge));
	args.push_back(std::make_unique<args::BoolArg>(isMyProgramCool));

	return args;
}