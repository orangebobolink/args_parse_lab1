#include "testUtils.hpp"

namespace test_utils
{
	TestStruct createTestCase(const std::vector<const char*>& strings) {
		int size = strings.size();
		std::unique_ptr<const char* []> stringArray(new const char* [size]);

		for (int i = 0; i < size; ++i) {

			stringArray[i] = strings[i];
		}

		return { size, std::move(stringArray) };
	}

	std::vector<TestStruct> createTestCases(const std::vector<std::vector<const char*>>& testCasesStrings) {
		std::vector<TestStruct> testCases;
		for (const auto& testCaseStrings : testCasesStrings) {
			testCases.push_back(createTestCase(testCaseStrings));
		}
		return std::move(testCases);
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

	types::Result<bool> helpFunc(const args::Arg* arg, const args_parse::Parser* parser)
	{
		std::cout << "--" << arg->getLongArg() << std::endl;
		return { true };
	}
	types::Result<bool> defaultFunc(const args::Arg* arg, const args_parse::Parser* parser)
	{
		std::cout << "--" << arg->getLongArg() << std::endl;
		return { true };
	}

	std::vector<std::unique_ptr<args::Arg>> test_utils::getTestArgs()
	{
		args::EmptyArg help('h', "help",
			"It's help operation",
			helpFunc);

		args::ValueArg<std::string> output('o', "output",
			"It's output operation",
			defaultFunc, &stringValidator);

		args::MultyEmptyArg version('v', "version",
			"It's version operation",
			defaultFunc, 3);

		args::ValueArg<int> giveMyAge('g', "giveMyAge",
			"It has to show my age",
			defaultFunc, &intValidator);

		args::ValueArg<bool> isMyProgramCool('i', "isMyProgramCool",
			"It has to show you the truth",
			defaultFunc, &boolValidator);

		std::vector< std::unique_ptr<args::Arg>> args;

		args.push_back(std::make_unique<args::EmptyArg>(help));
		args.push_back(std::make_unique<args::MultyEmptyArg>(version));
		args.push_back(std::make_unique < args::ValueArg<std::string>> (output));
		args.push_back(std::make_unique<args::ValueArg<int>>(giveMyAge));
		args.push_back(std::make_unique<args::ValueArg<bool>>(isMyProgramCool));

		return args;
	}
}