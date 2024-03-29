#include "args_parse/stringArg.cpp"
#include "args_parse/parser.hpp"
#include <iostream>
#include <args_parse/intArg.cpp>
#include <args_parse/boolArg.cpp>

using namespace args_parse;

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
	catch (const invalid_argument& err)
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