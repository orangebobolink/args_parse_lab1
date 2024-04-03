#pragma once
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
	class ParserService
	{
	public:
		/**
		* \brief Является ли строка оператором.
		* \param str - входная строка.
		* \return Тип оператора.
		*/
		static OperatorType isOperator(const std::string& str);
		/**
		 * \brief Является ли следующий аргумент значением.
		 * \param nextElement - след элемент.
		 * \param argAllowsUseValue - разрешены ли аргументы.
		*/
		static types::Result<bool> checkIfTheFollowingArgvIsAValue(const char* nextElement,
			const bool argAllowsUseValue);
		/**
		 * \brief Состоит ли item из аргументов и значений.
		*/
		static types::Result<int> itemConsistsOfAnArgumentAndAValue(std::string& value,
			std::string& item,
			std::string& longArg,
			int index
		);
		/**
		 * \brief Проверка состоит ли item из аргументов и значений.
		*/
		static bool checkItemConsistsOfAnArgumentAndAValue(std::string& item,
			std::string& longArg
		);
		/**
		 * \brief Проверка написан ли аргумент в неполной форме.
		*/
		static bool checkArgumentIsWrittenInAnIncompleteForm(std::string& item,
			std::string& longArg
		);
		/**
		 * \brief Есть ли знак = в строке.
		*/
		static void checkTheItemCheckContainsAnEqualSign(std::string& item, std::string& value);
	};
}