#include <args/arg.hpp>
#include <vector>
#include <memory>
#include <args_parse/parser.hpp>
#include <iostream>

std::vector<std::unique_ptr<args::Arg>> getTestArgs();
args_parse::Parser getParser(const int argc, const char** argv);

int main(int argc, const char** argv)
{
	auto parser = getParser(argc, argv);

	auto result = parser.parse();

	if (!result.data.has_value()) std::cout << result.error << std::endl;
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
		[](args_parse::Parser* parser, args::Arg<void>* arg) -> types::Result<bool> { /*...*/ });

	args::MultyEmptyArg version('v', "version",
		"It's version operation",
		[](args::Arg* arg)
		{
			return types::Result<bool>(true, true);
		}, 3);

	args::ValueArg<std::string> output('o', "output",
		"It's output operation",
		[](args::Arg* arg)
		{
			return types::Result<bool>(true, true);
		});

	args::ValueArg<int> giveMyAge('g', "giveMyAge",
		"It has to show my age",
		[](args::Arg* arg)
		{
			return types::Result<bool>(true, true);
		});

	args::ValueArg<bool> isMyProgramCool('i', "isMyProgramCool",
		"It has to show you the truth",
		[](args::Arg* arg)
		{
			return types::Result<bool>(true, true);
		});

	std::vector< std::unique_ptr<args::Arg>> args;

	args.push_back(std::make_unique<args::EmptyArg>(help));
	args.push_back(std::make_unique<args::MultyValueArg<void>>(version));
	args.push_back(std::make_unique<args::ValueArg<std::string>>(output));
	args.push_back(std::make_unique<args::ValueArg<int>>(giveMyAge));
	args.push_back(std::make_unique<args::ValueArg<bool>>(isMyProgramCool));

	return std::move(args);
}