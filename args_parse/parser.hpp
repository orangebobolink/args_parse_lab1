#pragma once
#include "arg.hpp"
#include <vector> 
#include <tuple>

using namespace std;

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
		vector<Arg> args;
		/**
		 * \brief Является ли строка оператором.
		 * \param str - входная строка. 
		 * \return Тип оператора.
		 */
		OperatorType isOperator(string str);
		/**
		 * \brief Поиск длинного оператора по всем известным парсеру операторов.
		 * \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \return Найденный оператор.
		 */
		Arg findLongOperator(string item, string& value) const;
		/**
		 * \brief Поиск короткого оператора по всем известным парсеру операторов.
		 * \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \return Найденный оператор.
		 */
		Arg findShortOperator(string item, string& value) const;
		/**
		 * \brief Получение оператора.
		* \param item Предпологаемый оператор.
		 * \param value Возможное значение оператора.
		 * \return Кортеж оператора и значения.
		 * \attention Если value = "", то значение у оператора нет.
		 */
		tuple<Arg, string> getOperator(string item, OperatorType operatorType) const;
		bool checkIfTheFollowingArgvIsAValue(const char* nextElement, Arg foundOperator);
	public:
		explicit Parser(int argc,
			const char** argv);
		~Parser();

		bool parse();
		void addArg(Arg arg);
		void addArgs(vector<Arg> args);
	};
}