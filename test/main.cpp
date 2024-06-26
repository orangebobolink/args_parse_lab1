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
		auto boolValidator = args::Validator<bool>();

		REQUIRE(boolValidator.validate(boolStr).data.value());
		REQUIRE_FALSE(boolValidator.validate(numberStr).data.value());
		REQUIRE_FALSE(boolValidator.validate(stringStr).data.value());
	}

	SECTION("Int validation") {
		auto intValidator = args::Validator<int>();

		REQUIRE(intValidator.validate(numberStr).data.value());
		REQUIRE_FALSE(intValidator.validate(boolStr).data.value());
		REQUIRE_FALSE(intValidator.validate(stringStr).data.value());
	}

	SECTION("String validation") {
		auto stringValidator = args::Validator<std::string>();

		REQUIRE(stringValidator.validate(stringStr).data.value());
		REQUIRE(stringValidator.validate(boolStr).data.value());
		REQUIRE_FALSE(stringValidator.validate(numberStr).data.value());
	}
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