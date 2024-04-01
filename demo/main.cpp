#include "args_parse/parser.hpp"
#include <iostream>
#include <args/arg.hpp>
#include <args/boolArg.hpp>
#include <args/intArg.hpp>
#include <args/stringArg.hpp>

using namespace args_parse;
using namespace args;

std::vector<Arg> getTestArgs();

int main(int argc, const char ** argv)
{
	Parser parcer(argc, argv);

	auto args = getTestArgs();
	parcer.addArgs(args);

	try
	{
		parcer.parse();
	}
	catch (const std::invalid_argument& err)
	{
		std::cout << err.what()<< std::endl;
	}
}

std::vector<Arg> getTestArgs()
{
	std::vector<Arg> args;

	StringArg help('h', "help",
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

	args.push_back(help);
	args.push_back(output);
	args.push_back(giveMyAge);
	args.push_back(isMyProgramCool);

	return args;
}