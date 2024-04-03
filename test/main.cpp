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

	SECTION("Bool validation") {
		args::BoolArg arg(' ', "", "", [](std::string value) {return types::Result<bool>(true, true); });

		REQUIRE(arg.validateValue(boolStr));
		REQUIRE_FALSE(arg.validateValue(numberStr));
		REQUIRE_FALSE(arg.validateValue(stringStr));
	}

	SECTION("Int validation") {
		args::IntArg arg(' ', "", "", [](std::string value) {return types::Result<bool>(true, true); });

		REQUIRE(arg.validateValue(numberStr));
		REQUIRE_FALSE(arg.validateValue(boolStr));
		REQUIRE_FALSE(arg.validateValue(stringStr));
	}

	SECTION("String validation") {
		args::StringArg arg(' ', "", "", [](std::string value) {return types::Result<bool>(true, true); });

		REQUIRE(arg.validateValue(stringStr));
		REQUIRE(arg.validateValue(boolStr));
		REQUIRE_FALSE(arg.validateValue(numberStr));
	}
}

TEST_CASE("Parser positive", "[dummy][section]")
{
	SECTION("Passing short and long arguments")
	{
		std::cout << "1 SECTION" << std::endl;

		std::vector<std::vector<const char*>> testCasesStrings =
		{
			{ " ", "-h", "--output", "hello" },
			{ " ", "-h", "-o", "hello" },
			{ " ", "--help", "--giveMyAge", "20" }
		};
		auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

		for (auto& testCase : testCases)
		{
			bool assert = runParce(testCase.first, testCase.second.get()).success;
			REQUIRE(assert);
		}
	}

	SECTION("Transfer of an incomplete name")
	{
		std::cout << "2 SECTION" << std::endl;

		std::vector<std::vector<const char*>> testCasesStrings =
		{
			{" ", "--hel"},
			{" ", "--o", "Hello"}
		};
		auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

		for (auto& testCase : testCases)
		{
			bool assert = runParce(testCase.first, testCase.second.get()).success;
			REQUIRE(assert);
		}
	}

	SECTION("A glued set of arguments")
	{
		std::cout << "3 SECTION" << std::endl;

		std::vector<std::vector<const char*>> testCasesStrings =
		{
			{" ", "-hoGlued"},
			{" ", "-ho=Glued"},
			{ " ", "-ho", "Glued"},
			{" ", "-hv"}
		};
		auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

		for (auto& testCase : testCases)
		{
			bool assert = runParce(testCase.first, testCase.second.get()).success;
			REQUIRE(assert);
		}
	}

	SECTION("Passing parameters")
	{
		std::cout << "4 SECTION" << std::endl;

		std::vector<std::vector<const char*>> testCasesStrings =
		{
			{ " ", "-h", "--output", "This is output" },
			{ " ", "-h", "--output=This is output" },
			{ " ", "-h", "--outputThis is output" }
		};
		auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

		for (auto& testCase : testCases)
		{
			bool assert = runParce(testCase.first, testCase.second.get()).success;
			REQUIRE(assert);
		}
	}
}

TEST_CASE("Parser negative", "[dummy][section][throws]")
{
	std::vector<std::vector<const char*>> testCasesStrings =
	{
		{" ", "-d"},
		{" ", "Value"},
		{ " ", "-h", "-d" },
		{ " ", "--help", "-s" },
		{ " ", "--giveMyAge", "hello" },
		{ " ", "--giveMyAge"},
		{ " ", "-hs" }
	};
	auto testCases = std::move(test_utils::createTestCases(testCasesStrings));

	for (auto& testCase : testCases)
	{
		bool assert = runParce(testCase.first, testCase.second.get()).success;
		REQUIRE_FALSE(assert);
	}
}