#pragma once
#include <types/result.hpp>
namespace args_parse
{
	/**
	 * \brief ��� ����������� ��������, ������� ��� �����������.
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
	 * \brief �������� �� ������ ����������.
	 * \param str - ������� ������.
	 * \return ��� ���������.
	 */
		static OperatorType isOperator(const std::string str);
		static types::Result<bool> checkIfTheFollowingArgvIsAValue(const char* nextElement,
			const bool argAllowsUseValue);
	};

}