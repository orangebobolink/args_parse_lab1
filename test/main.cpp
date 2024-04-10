#include "testUtils.hpp"
#include <catch2/catch_all.hpp>
#include <iostream>

types::Result<bool> runParce(int argc, const char* argv[])
{
	auto parser = test_utils::getParser(argc, argv);

	return parser.parse();
}

TEST_CASE("Validation", "[dummy][section]")
{
	std::string numberStr = "10";
	std::string boolStr = "true";
	std::string stringStr = "something";

	/*SECTION("Bool validation") {
		args::ValueArg<bool> arg(' ', "", "",
			[]()
			{return types::Result<bool>(true); });

		REQUIRE(arg.validateValue(boolStr));
		REQUIRE_FALSE(arg.validateValue(numberStr));
		REQUIRE_FALSE(arg.validateValue(stringStr));
	}

	SECTION("Int validation") {
		args::ValueArg<int> arg(' ', "", "",
			[]()
			{return types::Result<bool>(true); });

		REQUIRE(arg.validateValue(numberStr));
		REQUIRE_FALSE(arg.validateValue(boolStr));
		REQUIRE_FALSE(arg.validateValue(stringStr));
	}

	SECTION("String validation") {
		args::StringArg arg(' ', "", "",
			[]()
			{return types::Result<bool>(true); });

		REQUIRE(arg.validateValue(stringStr));
		REQUIRE(arg.validateValue(boolStr));
		REQUIRE_FALSE(arg.validateValue(numberStr));
	}*/
}

TEST_CASE("Parser positive", "[dummy][section]")
{
	SECTION("Passing short and long arguments")
	{
		std::cout << "1 SECTION" << std::endl;

		const std::vector<std::vector<const char*>> testCasesStrings =
		{
			{ " ", "-h", "--output", "hello" },
			{ " ", "-h", "-o", "hello" },
			{ " ", "--help", "--giveMyAge", "20" }
		};
		auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

		for (auto& testCase : testCases)
		{
			const bool assert = runParce(testCase.size, testCase.arguments.get()).isOk();
			REQUIRE(assert);
		}
	}

	SECTION("Transfer of an incomplete name")
	{
		std::cout << "2 SECTION" << std::endl;

		const std::vector<std::vector<const char*>> testCasesStrings =
		{
			{" ", "--hel"},
			{" ", "--o", "Hello"}
		};
		auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

		for (auto& testCase : testCases)
		{
			const bool assert = runParce(testCase.size, testCase.arguments.get()).isOk();
			REQUIRE(assert);
		}
	}

	SECTION("A glued set of arguments")
	{
		std::cout << "3 SECTION" << std::endl;

		const std::vector<std::vector<const char*>> testCasesStrings =
		{
			{" ", "-hoGlued"},
			{" ", "-ho=Glued"},
			{ " ", "-ho", "Glued"},
			{" ", "-hv"}
		};
		auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

		for (auto& testCase : testCases)
		{
			const bool assert = runParce(testCase.size, testCase.arguments.get()).isOk();
			REQUIRE(assert);
		}
	}

	SECTION("Passing parameters")
	{
		std::cout << "4 SECTION" << std::endl;

		const std::vector<std::vector<const char*>> testCasesStrings =
		{
			{ " ", "-h", "--output", "This is output" },
			{ " ", "-h", "--output=This is output" },
			{ " ", "-h", "--outputThis is output" }
		};
		auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

		for (auto& testCase : testCases)
		{
			const bool assert = runParce(testCase.size, testCase.arguments.get()).isOk();
			REQUIRE(assert);
		}
	}

	SECTION("Multy args")
	{
		std::cout << "5 SECTION" << std::endl;

		const std::vector<std::vector<const char*>> testCasesStrings =
		{
			{ " ", "-v", "-v", "-v"},
			{ " ", "-v", "-v", "--version"},
			{ " ", "-v", "--version", "-h", "-v"}
		};
		auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

		for (auto& testCase : testCases)
		{
			const bool assert = runParce(testCase.size, testCase.arguments.get()).isOk();
			REQUIRE(assert);
		}
	}
}

TEST_CASE("Parser negative", "[dummy][section][throws]")
{
	const std::vector<std::vector<const char*>> testCasesStrings =
	{
		{" ", "-d"},
		{" ", "Value"},
		{ " ", "-h", "-d" },
		{ " ", "--help", "-s" },
		{ " ", "--giveMyAge", "hello" },
		{ " ", "--giveMyAge"},
		{ " ", "-hs" },
		{" ", "-h", "--help"},
		{" ", "-v", "-v", "-v", "-v"},
	};

	const auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

	for (auto& testCase : testCases)
	{
		const bool assert = runParce(testCase.size, testCase.arguments.get()).isOk();
		REQUIRE_FALSE(assert);
	}
}