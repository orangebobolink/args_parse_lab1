#pragma once
#include <string>
#include <typeinfo>
#include <types/result.hpp>

namespace args
{
	class Arg
	{
	private:
		/// Описание аргумента.
		std::string description = "";
	protected:
		char shortArg = ' ';
		std::string longArg = "";
		types::Result<bool>(*processFunction)();
		bool hasValue = false;
		std::string value = "";
		int usageCount = 0;
		bool allowMultyValues = false;
		int maxUsageCount = 1;

	public:
		bool getHasValue() const;
		int getMaxUsageCount() const;
		void setValue(const std::string& value);
		std::string getValue() const;

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processFunction)());

		std::string getDescriptiong() const;
		void setDescription(std::string description);
		char getShortArg() const;
		std::string getLongArg() const;
		bool virtual validateValue(std::string value);

		virtual types::Result<bool> process();
		void incrementUsageCount();
		void setUsageCount(int count);
		int getUsageCount() const;
		bool getAllowMultyValues() const;
	};
}