#pragma once
#include <string>
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
		bool hasValue = false;
		char shortArg = ' ';
		std::string longArg = "";
		types::Result<bool>(*processFunction)(Arg* arg, args_parse::Parser* parser);
		int usageCount = 0;
		bool allowMultyValues = false;
		int maxUsageCount = 1;

	public:
		virtual ~Arg() = default;
		bool getHasValue() const;
		int getMaxUsageCount() const;
		void setValue(const std::string& value);
		std::string getValue() const;

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(Arg* arg, args_parse::Parser* parser));

		std::string getDescription() const;
		void setDescription(std::string description);
		char getShortArg() const;
		std::string getLongArg() const;
		void incrementUsageCount();
		void setUsageCount(int count);
		int getUsageCount() const;
		bool getAllowMultyValues() const;

		bool virtual tryParse(std::string value) = 0;
		virtual types::Result<bool> process(args_parse::Parser* parser) = 0;
	};

	template <typename T>
	class ValueArg<T> : public Arg
	{
	public:
		ValueArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(Arg* arg, args_parse::Parser* parser))
			: Arg(shortArg, longArg, description, process)
		{
			this->hasValue = true;
		}

		bool tryParse(std::string value) override;
		types::Result<bool> process(args_parse::Parser* parser) override;
	};

	class EmptyArg : public Arg
	{
	public:
		EmptyArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(Arg* arg, args_parse::Parser* parser))
			: Arg(shortArg, longArg, description, process)
		{
			this->hasValue = false;
		}

		bool tryParse(std::string value) override;
		types::Result<bool> process(args_parse::Parser* parser) override;
	};

	class MultyEmptyArg : public EmptyArg
	{
	public:
		MultyEmptyArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(Arg* arg, args_parse::Parser* parser),
			int maxUsageCount = 3)
			: EmptyArg(shortArg, longArg, description, process)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process(args_parse::Parser* parser) override;
	};

	template <typename T>
	class MultyValueArg : public ValueArg<T>
	{
	public:
		MultyValueArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(Arg* arg, args_parse::Parser* parser),
			int maxUsageCount = 3)
			: EmptyArg(shortArg, longArg, description, process)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process(args_parse::Parser* parser) override;
	};
}
