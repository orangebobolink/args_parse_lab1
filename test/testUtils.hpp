#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "args/boolArg.hpp"
#include "args/emptyArg.hpp"
#include "args/intArg.hpp"
#include "args/stringArg.hpp"
#include "args_parse/parser.hpp"

namespace test_utils
{
	/**
		* \brief Получем настроенный парсер.
	*/
	args_parse::Parser getParser(const int argc, const char** argv);
	/**
		* \brief Получем тестовый набор аргументов.
	*/
	std::vector< std::unique_ptr<args::Arg>> getTestArgs();
	/**
		* \brief Создаем тестовый случай.
	*/
	std::pair<int, std::unique_ptr<const char* []>> createTestCase(const std::vector<const char*>& strings);
	/**
		* \brief Создаем набор тестовых случаев.
	*/
	std::vector<std::pair<int, std::unique_ptr<const char* []>>> createTestCases(const std::vector<std::vector<const char*>>& testCasesStrings);
}