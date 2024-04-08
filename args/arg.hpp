#pragma once
#include <functional>
#include <string>
#include <types/result.hpp>
#include <optional>

#include "args_parse/parser.hpp"

namespace args
{
	template<typename T>
	class ITryParse
	{
	public:
		virtual ~ITryParse() = default;
		virtual std::optional<T> tryParse(std::string value) = 0;
	};

	class Arg
	{
		/// Описание аргумента.
		std::string description = "";
	protected:
		char shortArg = ' ';
		std::string longArg = "";
		const std::function<types::Result<bool>(args_parse::Parser*, Arg*)> processArg;
		bool hasValue = false;
		bool allowMultyValues = false;

	public:
		virtual ~Arg() = default;
		bool getHasValue() const;

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			const std::function<types::Result<bool>(args_parse::Parser* parser, Arg*)> process);

		std::string getDescriptiong() const;
		void setDescription(std::string description);
		char getShortArg() const;
		std::string getLongArg() const;
		bool virtual validateValue(std::string value);
		bool getAllowMultyValues() const;

		virtual types::Result<bool> process(args_parse::Parser* parser);
		virtual void incrementUsageCount() = 0;
		virtual void setUsageCount(int count) = 0;
		virtual int getUsageCount() const = 0;
		virtual int getMaxUsageCount() const = 0;
	};

	class EmptyArg : public Arg
	{
	public:
		EmptyArg(char shortArg,
			std::string longArg,
			std::string description,
			const std::function<types::Result<bool>(args_parse::Parser*, Arg*)> process)
			: Arg(shortArg, longArg, description, process)
		{
			this->hasValue = false;
		}

		bool validateValue(std::string value) override;
	};

	template<typename T>
	class ValueArg : public Arg
	{
	protected:
		T value;
		ITryParse<T>* tryparse{};
	public:
		ValueArg(char shortArg,
			std::string longArg,
			std::string description,
			const std::function<types::Result<bool>(args_parse::Parser*, Arg*)> process,
			ITryParse<T>* tryparse)
			: Arg(shortArg, longArg, description, process)
		{
			this->hasValue = true;
			this->tryparse = tryparse;
		}

		bool validateValue(std::string value) override;
		types::Result<bool> process(args_parse::Parser* parser) override;
		void setValue(T value);
		T getValue() const;
	};

	template<typename T>
	class MultyValueArg : public ValueArg<T>
	{
	private:
		int usageCount = 0;
		int maxUsageCount = 1;
	public:
		MultyValueArg(char shortArg,
			std::string longArg,
			std::string description,
			const std::function<types::Result<bool>(args_parse::Parser*, Arg*)> process)
			: ValueArg<T>(shortArg, longArg, description, process)
		{
			this->hasValue = true;
		}

		bool validateValue(std::string value) override;
		types::Result<bool> process(args_parse::Parser* parser) override;
	};

	class MultyEmptyArg : public EmptyArg
	{
	private:
		int usageCount = 0;
		int maxUsageCount = 1;
	public:
		MultyEmptyArg(char shortArg,
			std::string longArg,
			std::string description,
			const std::function<types::Result<bool>(args_parse::Parser*, Arg*)> process)
			: EmptyArg(shortArg, longArg, description, process)
		{
			this->hasValue = true;
		}

		types::Result<bool> process(args_parse::Parser* parser) override;
	};
}
