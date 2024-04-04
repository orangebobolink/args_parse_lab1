#include <args/arg.hpp>
#include <vector>
#include <memory>
#include <args/emptyArg.hpp>
#include <args_parse/parser.hpp>
#include <multy_args/multyEmptyArg.hpp>
#include <args/stringArg.hpp>
#include <args/intArg.hpp>
#include <args/boolArg.hpp>
#include <iostream>

std::vector<std::unique_ptr<args::Arg>> getTestArgs();
args_parse::Parser getParser(const int argc, const char** argv);

int main(int argc, const char** argv)
{
	auto parser = getParser(argc, argv);

	auto result = parser.parse();

	if (!result.success) std::cout << result.error << std::endl;
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


std::vector<std::unique_ptr<args::Arg>> getTestArgs()
{
	args::EmptyArg help('h', "help",
		"It's help operation",
		[]()
		{
			std::cout << "Help" << std::endl;
			return types::Result(true, true);
		});

	multy_args::MultyEmptyArg version('v', "version",
		"It's version operation",
		[]()
		{
			std::cout << "Version" << std::endl;
			return types::Result(true, true);
		}, 3);

	args::StringArg output('o', "output",
		"It's output operation",
		[]()
		{
			return types::Result(true, true);
		});

	args::IntArg giveMyAge('g', "giveMyAge",
		"It has to show my age",
		[]()
		{
			return types::Result(true, true);
		});

	args::BoolArg isMyProgramCool('i', "isMyProgramCool",
		"It has to show you the truth",
		[]()
		{
			return types::Result(true, true);
		});

	std::vector< std::unique_ptr<args::Arg>> args;

	args.push_back(std::make_unique<args::EmptyArg>(help));
	args.push_back(std::make_unique<multy_args::MultyEmptyArg>(version));
	args.push_back(std::make_unique<args::StringArg>(output));
	args.push_back(std::make_unique<args::IntArg>(giveMyAge));
	args.push_back(std::make_unique<args::BoolArg>(isMyProgramCool));

	return args;
}