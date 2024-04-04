#include "testUtils.hpp"
#include <multy_args/multyEmptyArg.hpp>

namespace test_utils
{
	std::pair<int, std::unique_ptr<const char* []>> test_utils::createTestCase(const std::vector<const char*>& strings) {
		int size = strings.size();
		std::unique_ptr<const char* []> stringArray(new const char* [size]);

		for (int i = 0; i < size; ++i) {

			stringArray[i] = strings[i];
		}

		return std::make_pair(size, std::move(stringArray));
	}

	std::vector<std::pair<int, std::unique_ptr<const char* []>>> test_utils::createTestCases(const std::vector<std::vector<const char*>>& testCasesStrings) {
		std::vector<std::pair<int, std::unique_ptr<const char* []>>> testCases;
		for (const auto& testCaseStrings : testCasesStrings) {
			testCases.push_back(createTestCase(testCaseStrings));
		}
		return std::move(testCases);
	}

	args_parse::Parser test_utils::getParser(const int argc, const char** argv)
	{
		args_parse::Parser parser(argc, argv);
		auto args = std::move(getTestArgs());

		for (auto& arg : args)
		{
			parser.addArg(std::move(arg));
		}

		return parser;
	}

	std::vector<std::unique_ptr<args::Arg>> test_utils::getTestArgs()
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
}