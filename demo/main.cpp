#include "args_parse/parser.hpp"
#include <iostream>
#include <args/arg.hpp>
#include <args/boolArg.hpp>
#include <args/intArg.hpp>
#include <args/stringArg.hpp>

using namespace args_parse;
using namespace args;
using namespace std;

vector<Arg> getTestArgs();

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

vector<Arg> getTestArgs()
{
	vector<Arg> args;

	StringArg help('h', "help",
		"It's help operation",
		[]()
		{
			cout << "Something" << endl;
		});

	StringArg output('o', "output",
		"It's output operation",
		[](string value)
		{
			cout << value << endl;
		});

	IntArg giveMyAge('g', "giveMyAge",
		"It has to show my age",
		[](string value)
		{
			cout << value << endl;
		});

	BoolArg isMyProgramCool('i', "isMyProgramCool",
		"It has to show you the truth",
		[](string value)
		{
			cout << value << endl;
		});

	args.push_back(help);
	args.push_back(output);
	args.push_back(giveMyAge);
	args.push_back(isMyProgramCool);

	return args;
}