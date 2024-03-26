#include "args_parse/stringArg.cpp"
#include "args_parse/parcer.hpp"
#include <iostream>

using namespace args_parse;

int main(int argc, const char ** argv)
{
	Parcer parcer(argc, argv);

	StringArg help('h',"help",
		"It's help operation",
		[]()
		{
			cout << "Something" << endl;
		});

	parcer.addArg((args_parse::StringArg::Arg)help);

	try
	{
		parcer.parce();
	}
	catch (const invalid_argument err)
	{
		std::cout << err.what()<< std::endl;
	}
}
