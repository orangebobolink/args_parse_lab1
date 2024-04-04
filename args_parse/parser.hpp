#pragma once
#include "args/arg.hpp"
#include "parserService.hpp"
#include <vector> 

namespace args_parse
{
	class Parser
	{
	private:
		int argc = 0;
		const char** argv;
		std::vector<std::unique_ptr<args::Arg>> args;
		/**
		 * \brief Поиск длинного оператора по всем известным парсеру операторов.
		 * \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \return Найденный оператор.
		 */
		types::Result<int> findLongOperator(std::string& item, std::string& value) const;
		/**
		 * \brief Поиск короткого оператора по всем известным парсеру операторов.
		 * \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \param indexVector Вектор индексов аргуемнтов
		 * \return Найденный оператор.
		 */
		types::Result<bool> findShortOperator(std::string& item, std::string& value, std::vector<int>& indexVector) const;
		/**
		 * \brief Получение оператора.
		 * \param item Предпологаемый оператор.
		 * \param operatorType Тип оператора.
		 * \return Кортеж оператора и значения.
		 * \attention Если value = "", то значение у оператора нет.
		 */
		types::Result<std::vector<int>> getOperator(std::string& item, OperatorType operatorType) const;
		types::Result<bool> parseNextElement(args::Arg* foundOperator, const char* nextElement, int& i) const;

	public:
		Parser(int argc,
			const char** argv);

		types::Result<bool> parse() const;
		void addArg(std::unique_ptr<args::Arg> arg);
		void addArgs(std::vector<std::unique_ptr<args::Arg>> args);
	};
}
