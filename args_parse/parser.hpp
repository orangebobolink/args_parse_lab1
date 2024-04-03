#pragma once
#include <vector> 
#include <tuple>
#include "args/arg.hpp"
#include <types/result.hpp>

namespace args_parse
{

	/**
	 * \brief Тип операторова короткий, длинный или неизвестный.
	 */
	enum class OperatorType
	{
		LONG,
		SHORT,
		NOPE
	};

	class Parser
	{
	private:
		int argc = 0;
		const char** argv;
		std::vector<std::unique_ptr<args::Arg>> args;
		/**
		 * \brief Является ли строка оператором.
		 * \param str - входная строка.
		 * \return Тип оператора.
		 */
		static OperatorType isOperator(const std::string str);
		/**
		 * \brief Поиск длинного оператора по всем известным парсеру операторов.
		 * \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \return Найденный оператор.
		 */
		types::Result<int> findLongOperator(std::string item, std::string& value) const;
		/**
		 * \brief Поиск короткого оператора по всем известным парсеру операторов.
		 * \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \return Найденный оператор.
		 */
		types::Result<bool> findShortOperator(std::string item, std::string& value, std::vector<int>& indexVector) const;
		/**
		 * \brief Получение оператора.
		* \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \return Кортеж оператора и значения.
		 * \attention Если value = "", то значение у оператора нет.
		 */
		types::Result<std::vector<int>> getOperator(std::string item, OperatorType operatorType) const;
		types::Result<bool> checkIfTheFollowingArgvIsAValue(const char* nextElement, const bool argAllowsUseValue);
	public:
		Parser(int argc,
			const char** argv);

		types::Result<bool> parse();
		void addArg(std::unique_ptr<args::Arg> arg);
		void addArgs(std::vector<std::unique_ptr<args::Arg>> args);
	};
}
