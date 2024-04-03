#include <catch2/catch_all.hpp>

#include <iostream>
#include <memory>

#include "args/boolArg.hpp"
#include "args/emptyArg.hpp"
#include "args/intArg.hpp"
#include "args/stringArg.hpp"
#include "args_parse/parser.hpp"

args_parse::Parser getParser(const int argc, const char** argv);
std::vector< std::unique_ptr<args::Arg>> getTestArgs();
bool runParce(int argc, const char* argv[]);

TEST_CASE("Validation", "[dummy][section]")
{
	std::string numberStr = "10";
	std::string boolStr = "true";
	std::string stringStr = "something";

	SECTION("Bool validation") {
		args::BoolArg arg(' ', "", "", [](std::string value) {});

		REQUIRE(arg.validateValue(boolStr));
		REQUIRE_FALSE(arg.validateValue(numberStr));
		REQUIRE_FALSE(arg.validateValue(stringStr));
	}

	SECTION("Int validation") {
		args::IntArg arg(' ', "", "", [](std::string value) {});

		REQUIRE(arg.validateValue(numberStr));
		REQUIRE_FALSE(arg.validateValue(boolStr));
		REQUIRE_FALSE(arg.validateValue(stringStr));
	}

	SECTION("String validation") {
		args::StringArg arg(' ', "", "", [](std::string value) {});

		REQUIRE(arg.validateValue(stringStr));
		REQUIRE(arg.validateValue(boolStr));
		REQUIRE_FALSE(arg.validateValue(numberStr));
	}
}

TEST_CASE("Parser positive", "[dummy][section]")
{
	SECTION("Passing short and long arguments")
	{
		std::vector<std::pair<int, std::unique_ptr<const char* []>>> testCases;
		auto array1 = new const char* [4] {" ", "-h", "--output", "hello"};
		auto array2 = new const char* [4] {" ", "-h", "-o", "hello"};
		auto array3 = new const char* [4] {" ", "--help", "--giveMyAge", "10"};
		testCases.push_back(std::make_pair(4, std::unique_ptr<const char* []>(array1)));
		testCases.push_back(std::make_pair(4, std::unique_ptr<const char* []>(array2)));
		testCases.push_back(std::make_pair(4, std::unique_ptr<const char* []>(array3)));

		for (auto& testCase : testCases)
		{
			bool assert = runParce(testCase.first, testCase.second.get());
			REQUIRE(assert);
		}
	}

	SECTION("Transfer of an incomplete name")
	{
		std::vector<std::pair<int, std::unique_ptr<const char* []>>> testCases;
		auto array1 = new const char* [2] {" ", "--hel"};
		auto array2 = new const char* [3] {" ", "--o", "Hello"};
		testCases.push_back(std::make_pair(2, std::unique_ptr<const char* []>(array1)));
		testCases.push_back(std::make_pair(3, std::unique_ptr<const char* []>(array2)));

		for (auto& testCase : testCases)
		{
			bool assert = runParce(testCase.first, testCase.second.get());
			REQUIRE(assert);
		}
	}

	SECTION("A glued set of arguments")
	{
		std::vector<std::pair<int, std::unique_ptr<const char* []>>> testCases;
		auto array1 = new const char* [2] {" ", "-hoGlued"};
		auto array2 = new const char* [2] {" ", "-ho=Glued"};
		auto array3 = new const char* [2] {" ", "-hv"};

		testCases.push_back(std::make_pair(2, std::unique_ptr<const char* []>(array1)));
		testCases.push_back(std::make_pair(2, std::unique_ptr<const char* []>(array2)));
		testCases.push_back(std::make_pair(2, std::unique_ptr<const char* []>(array3)));

		for (auto& testCase : testCases)
		{
			bool assert = runParce(testCase.first, testCase.second.get());
			REQUIRE(assert);
		}
	}

	SECTION("Passing parameters")
	{
		std::vector<std::pair<int, std::unique_ptr<const char* []>>> testCases;
		auto array2 = new const char* [4] { " ", "-h", "--output", "This is output" };
		auto array3 = new const char* [3] { " ", "-h", "--output=This is output" };
		auto array4 = new const char* [3] { " ", "-h", "--outputThis is output" };
		testCases.push_back(std::make_pair(4, std::unique_ptr<const char* []>(array2)));
		testCases.push_back(std::make_pair(3, std::unique_ptr<const char* []>(array3)));
		testCases.push_back(std::make_pair(3, std::unique_ptr<const char* []>(array4)));

		for (auto& testCase : testCases)
		{
			bool assert = runParce(testCase.first, testCase.second.get());
			REQUIRE(assert);
		}
	}
}

//TEST_CASE("Parser negative", "[dummy][section][throws]")
//{
//	SECTION("The parser does not contain an argument corresponding to the entered ones")
//	{
//		std::vector<std::tuple<int, std::string>> s = {
//			std::make_tuple<int, std::string>(2, {" ", "-d"}),
//
//		};
//
//		for (auto testCase : s)
//		{
//			REQUIRE_THROWS(
//				[]
//				{
//					auto parser = getParser(std::get<0>(testCase), std::get<1>(testCase));
//
//					parser.parse();
//				}());
//		}
//		REQUIRE_THROWS(
//			[]
//			{
//				auto parser = getParser(s[0].get<int>(), argv);
//
//				parser.parse();
//			}());
//
//		REQUIRE_THROWS(
//			[]
//			{
//				const char* argv[] = { " ", "-h", "-d" };
//				const int argc = 3;
//
//				auto parser = getParser(argc, argv);
//
//				parser.parse();
//			}());
//
//		REQUIRE_THROWS(
//			[]
//			{
//				const char* argv[] = { " ", "--help", "-s" };
//				const int argc = 3;
//
//				auto parser = getParser(argc, argv);
//
//				parser.parse();
//			}());
//
//		REQUIRE_THROWS(
//			[]
//			{
//				const char* argv[] = { " ", "--giveMyAge", "hello" };
//				const int argc = 3;
//
//				auto parser = getParser(argc, argv);
//
//				parser.parse();
//			}());
//	}
//}

bool runParce(int argc, const char* argv[])
{
	auto parser = getParser(argc, argv);

	return parser.parse();
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
		});

	args::EmptyArg version('v', "version",
		"It's version operation",
		[]()
		{
			std::cout << "Version" << std::endl;
		});

	args::StringArg output('o', "output",
		"It's output operation",
		[](std::string value)
		{
			std::cout << value << std::endl;
		});

	args::IntArg giveMyAge('g', "giveMyAge",
		"It has to show my age",
		[](std::string value)
		{
			std::cout << value << std::endl;
		});

	args::BoolArg isMyProgramCool('i', "isMyProgramCool",
		"It has to show you the truth",
		[](std::string value)
		{
			std::cout << value << std::endl;
		});

	std::vector< std::unique_ptr<args::Arg>> args;

	args.push_back(std::make_unique<args::EmptyArg>(help));
	args.push_back(std::make_unique<args::EmptyArg>(version));
	args.push_back(std::make_unique<args::StringArg>(output));
	args.push_back(std::make_unique<args::IntArg>(giveMyAge));
	args.push_back(std::make_unique<args::BoolArg>(isMyProgramCool));

	return args;
}