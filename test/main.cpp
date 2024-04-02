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
    const char* argv[] = { " ", "-h" };
    const int argc = 2;

    auto parser = getParser(argc, argv);

    bool assert = parser.parse();
    REQUIRE(assert);
}

TEST_CASE("Parser negative", "[dummy][section][throws]")
{
    SECTION("The parser does not contain an argument corresponding to the entered ones")
    {
        REQUIRE_THROWS(
            []
            {
                const char* argv[] = { " ", "-d" };
                const int argc = 2;

                auto parser = getParser(argc, argv);

	            parser.parse();
            }());

        REQUIRE_THROWS(
            []
            {
                const char* argv[] = { " ", "-h", "-d" };
                const int argc = 3;

                auto parser = getParser(argc, argv);

                parser.parse();
            }());

        REQUIRE_THROWS(
            []
            {
                const char* argv[] = { " ", "--help", "-s" };
                const int argc = 2;

                auto parser = getParser(argc, argv);

                parser.parse();
            }());
    }
}

args_parse::Parser getParser(const int argc, const char** argv)
{
    args_parse::Parser parser(argc, argv);
    auto args = move(getTestArgs());

    for(auto& arg : args)
    {
        parser.addArg(move(arg));
    }

    return parser;
}

std::vector<std::unique_ptr<args::Arg>> getTestArgs()
{
	args::EmptyArg help('h', "help",
	                    "It's help operation",
	                    []()
	                    {
		                    std::cout << "Something" << std::endl;
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
    args.push_back(std::make_unique<args::StringArg>(output));
    args.push_back(std::make_unique<args::IntArg>(giveMyAge));
    args.push_back(std::make_unique<args::BoolArg>(isMyProgramCool));

    return args;
}