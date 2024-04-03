#pragma once
#include <types/result.hpp>
namespace args_parse
{
	/**
	 * \brief “ип операторова короткий, длинный или неизвестный.
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
	 * \brief явл€етс€ ли строка оператором.
	 * \param str - входна€ строка.
	 * \return “ип оператора.
	 */
		static OperatorType isOperator(const std::string str);
		static types::Result<bool> checkIfTheFollowingArgvIsAValue(const char* nextElement,
			const bool argAllowsUseValue);
	};

}