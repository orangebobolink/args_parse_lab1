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
		* \brief Выдает экземпляр парсера для тестов
	*/
	args_parse::Parser getParser(const int argc, const char** argv);
	/**
		* \brief Выдает экземпляр аргументов для тестов
	*/
	std::vector<std::unique_ptr<args::Arg>> getTestArgs();
	/**
		* \brief Задаем тестовые данные консоли
	*/
	TestStruct createTestCase(const std::vector<const char*>& strings);
	/**
		* \brief Задаем несколько тестовые данные консоли
	*/
	std::vector<TestStruct> createTestCases(const std::vector<std::vector<const char*>>& testCasesStrings);
}