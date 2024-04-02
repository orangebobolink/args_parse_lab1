#pragma once
#include <vector> 
#include <tuple>
#include "args/arg.hpp"

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
		std::vector<args::Arg*> args;
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
		int findLongOperator(std::string item, std::string& value) const;
		/**
		 * \brief Поиск короткого оператора по всем известным парсеру операторов.
		 * \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \return Найденный оператор.
		 */
		int findShortOperator(std::string item, std::string& value) const;
		/**
		 * \brief Получение оператора.
		* \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \return Кортеж оператора и значения.
		 * \attention Если value = "", то значение у оператора нет.
		 */
		std::tuple<args::Arg*, std::string> getOperator(std::string item, OperatorType operatorType) const;
		static bool checkIfTheFollowingArgvIsAValue(const char* nextElement, args::Arg* foundOperator);
	public:
		Parser(int argc,
			const char** argv);

		bool parse();
		void addArg(args::Arg* arg);
		void addArgs(std::vector<args::Arg*> args);
	};
}
