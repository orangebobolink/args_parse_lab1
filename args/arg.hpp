#pragma once
#include <string>
#include <typeinfo>

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
		void (*processFunction)();
		/// Логика с value.
		void (*processWithValueFunction)(std::string value);
		bool hasValue = false;
		std::string value = "";

	public:
		const bool getHasAValue()
		{
			return hasValue;
		}

		void setValue(std::string value)
		{
			value = value;
			hasValue = true;
		}

		const std::string getValue()
		{
			return value;
		}

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			void (*processFunction)(),
			void(*processWithValueFunction)(std::string value));

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			void (*processFunction)())
			: Arg(shortArg, longArg, description, processFunction, [](std::string value) {})
		{}

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			void (*processWithValueFunction)(std::string value))
			: Arg(shortArg, longArg, description, []() {}, [](std::string value) {})
		{}

		std::string getDescriptiong() const;
		void setDescription(std::string description);
		char getShortArg() const;
		std::string getLongArg() const;
		bool virtual validateValue(std::string value);

		void process();
		void processWithValue(std::string value);
	};
}