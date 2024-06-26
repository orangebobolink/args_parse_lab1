#pragma once
#include <string>

#include "args/arg.hpp"
#include "types/result.hpp"

namespace args_parse
{
	/**
	 * \brief Определяет тип оператора.
	 */
	enum class OperatorType
	{
		LONG,
		SHORT,
		NOPE
	};

	/**
	* \brief Определяет, является ли строка оператором.
	* \param str - исходная строка.
	* \return Тип оператора.
	*/
	OperatorType isOperator(const std::string& str);
	/**
		* \brief Определяет, является ли следующий элемент значением аргумента.
		* \param nextElement - следующий элемент.
		* \param argAllowsUseValue - разрешено ли использовать значение для аргумента.
	*/
	types::Result<bool> checkIfFollowingArgvIsValue(const char* nextElement,
	                                                const bool argAllowsUseValue);
	/**
		* \brief Определяет, состоит ли элемент из аргумента и значения.
	*/
	types::Result<int> itemConsistsOfArgumentAndValue(std::string& value,
		std::string& item,
		std::string& longArg,
		int index
	);
	/**
		* \brief Проверяет, состоит ли элемент из аргумента и значения.
	*/
	bool checkItemConsistsOfArgumentAndValue(std::string& item,
		const std::string& longArg
	);
	/**
		* \brief Проверяет, записан ли аргумент в неполной форме.
	*/
	bool checkArgumentIsWrittenInIncompleteForm(const std::string& item,
		std::string& longArg
	);
	/**
		* \brief Проверяет, содержит ли элемент знак равенства.
	*/
	void checkItemForEqualSign(std::string& item, std::string& value);
	/**
		* \brief Проверяет, аргумент имеет значение.
	*/
	types::Result<bool> checkArgumentHasValue(args::Arg* foundOperator);
	/**
		* \brief Проверяет, аргумент имеет не валидное значение.
	*/
	types::Result<bool> checkArgumentHasNotInvalidValue(args::Arg* foundOperator);
	/**
		* \brief Проверяет, валидность аргумента.
	*/
	types::Result<bool> checkArgumentValidity(args::Arg* arg);

}
