#pragma once
#include <vector>
#include <memory>
#include "args_parse/parser.hpp"

namespace test_utils
{
	struct TestStruct
	{
		int size;
		std::unique_ptr<const char* []> arguments;

		TestStruct(int size, std::unique_ptr<const char* []> arguments)
			: size(size), arguments(move(arguments)) {}
	};
	/**
		* \brief ������� ����������� ������.
	*/
	args_parse::Parser getParser(const int argc, const char** argv);
	/**
		* \brief ������� �������� ����� ����������.
	*/
	std::vector<std::unique_ptr<args::Arg>> getTestArgs();
	/**
		* \brief ������� �������� ������.
	*/
	TestStruct createTestCase(const std::vector<const char*>& strings);
	/**
		* \brief ������� ����� �������� �������.
	*/
	std::vector<TestStruct> createTestCases(const std::vector<std::vector<const char*>>& testCasesStrings);
}