#pragma once
#include <string>
#include <typeinfo>
#include <types/result.hpp>

#include "args_parse/parser.hpp"

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
		types::Result<bool>(*processFunction)(Arg* arg, args_parse::Parser* parser);
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

	class ValueArg<T> : public Arg
	{
	public:
		ValueArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)())
			: Arg(shortArg, longArg, description, process)
		{
			this->hasValue = true;
		}

		bool validateValue(std::string value) override;
		types::Result<bool> process() override;
	};

	class MultyArg : public Arg
	{
	public:
		MultyArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processFunction)(),
			int maxUsageCount = 3)
			: EmptyArg(shortArg, longArg, description, processFunction)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process() override;
	};
}
