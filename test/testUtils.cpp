#include "testUtils.hpp"

namespace test_utils
{
	TestStruct test_utils::createTestCase(const std::vector<const char*>& strings) {
		int size = strings.size();
		std::unique_ptr<const char* []> stringArray(new const char* [size]);

		for (int i = 0; i < size; ++i) {

			stringArray[i] = strings[i];
		}

		return { size, std::move(stringArray) };
	}

	std::vector<TestStruct> test_utils::createTestCases(const std::vector<std::vector<const char*>>& testCasesStrings) {
		std::vector<TestStruct> testCases;
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
		args::ValueArg<void> help('h', "help",
			"It's help operation",
			[](args_parse::Parser* parser, args::Arg* arg)
			{
				return types::Result<bool>(true);
			});

		args::MultyEmptyArg version('v', "version",
			"It's version operation",
			[]()
			{
				std::cout << "Version" << std::endl;
				return types::Result(true);
			}, 3);

		args::StringArg output('o', "output",
			"It's output operation",
			[]()
			{
				return types::Result(true);
			});

		args::IntArg giveMyAge('g', "giveMyAge",
			"It has to show my age",
			[]()
			{
				return types::Result(true);
			});

		args::BoolArg isMyProgramCool('i', "isMyProgramCool",
			"It has to show you the truth",
			[]()
			{
				return types::Result(true);
			});

		std::vector< std::unique_ptr<args::Arg>> args;

		args.push_back(std::make_unique<args::EmptyArg>(help));
		args.push_back(std::make_unique<args::MultyEmptyArg>(version));
		args.push_back(std::make_unique<args::StringArg>(output));
		args.push_back(std::make_unique<args::IntArg>(giveMyAge));
		args.push_back(std::make_unique<args::BoolArg>(isMyProgramCool));

		return args;
	}
}