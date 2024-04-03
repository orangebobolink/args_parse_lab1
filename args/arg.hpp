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
		/// Может ли содержать value.
		/// Логика без value.
		types::Result<bool>(*processFunction)();
		/// Логика с value.
		types::Result<bool>(*processWithValueFunction)(std::string value);
		bool hasValue = false;
		std::string value = "";
		int usageCount = 0;
		bool allowMultyValues = false;

	public:
		const bool getHasAValue()
		{
			return hasValue;
		}

		void setValue(std::string value)
		{
			this->value = value;
			//hasValue = true;
		}

		const std::string getValue()
		{
			return value;
		}

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processFunction)(),
			types::Result<bool>(*processWithValueFunction)(std::string value));

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processFunction)())
			: Arg(shortArg, longArg, description, processFunction, [](std::string value) {return types::Result(true, true); })
		{}

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processWithValueFunction)(std::string value))
			: Arg(shortArg, longArg, description, []() {return types::Result(true, true); }, processWithValueFunction)
		{}

		std::string getDescriptiong() const;
		void setDescription(std::string description);
		char getShortArg() const;
		std::string getLongArg() const;
		bool virtual validateValue(std::string value);

		virtual types::Result<bool> process();
		virtual types::Result<bool> processWithValue(std::string value);
		void incrementUsageCount();
		void setUsageCount(int count);
		int getUsageCount() const;
		bool getAllowMultyValues() const;
	};
}