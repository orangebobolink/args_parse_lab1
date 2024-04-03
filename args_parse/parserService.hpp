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
		static OperatorType isOperator(const std::string& str);
		/**
		 * \brief �������� �� ��������� �������� ���������.
		 * \param nextElement - ���� �������.
		 * \param argAllowsUseValue - ��������� �� ���������.
		*/
		static types::Result<bool> checkIfTheFollowingArgvIsAValue(const char* nextElement,
			const bool argAllowsUseValue);
		/**
		 * \brief ������� �� item �� ���������� � ��������.
		*/
		static types::Result<int> itemConsistsOfAnArgumentAndAValue(std::string& value,
			std::string& item,
			std::string& longArg,
			int index
		);
		/**
		 * \brief �������� ������� �� item �� ���������� � ��������.
		*/
		static bool checkItemConsistsOfAnArgumentAndAValue(std::string& item,
			std::string& longArg
		);
		/**
		 * \brief �������� ������� �� �������� � �������� �����.
		*/
		static bool checkArgumentIsWrittenInAnIncompleteForm(std::string& item,
			std::string& longArg
		);
		/**
		 * \brief ���� �� ���� = � ������.
		*/
		static void checkTheItemCheckContainsAnEqualSign(std::string& item, std::string& value);
	};
}