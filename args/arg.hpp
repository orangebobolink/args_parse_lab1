#pragma once
#include <iostream>
#include <sstream>

#include "fwd_decl.hpp"
#include <string>
#include <types/result.hpp>

namespace args
{
	class Validator
	{
	public:
		virtual ~Validator() = default;
		virtual types::Result<bool> validate(std::string& value) = 0;
	};

	class IntValidator : public Validator
	{
		types::Result<bool> validate(std::string& value) override;
	};

	class BoolValidator : public Validator
	{
		types::Result<bool> validate(std::string& value) override;
	};

	class StringValidator : public Validator
	{
		types::Result<bool> validate(std::string& value) override;
	};

	class Arg
	{
	private:
		/// Описание аргумента.
		std::string description = "";
	protected:
		bool hasValue = false;
		bool canHasValue = false;
		char shortArg = ' ';
		std::string longArg = "";
		types::Result<bool>(*processFunction)(const Arg* arg, const args_parse::Parser* parser){};
		int usageCount = 0;
		bool allowMultyValues = false;
		int maxUsageCount = 1;

	public:
		virtual ~Arg() = default;
		bool getHasValue() const;
		bool getCanHasValue() const;
		int getMaxUsageCount() const;

		Arg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(const Arg* arg, const args_parse::Parser* parser));

		std::string getDescription() const;
		void setDescription(std::string& description);
		char getShortArg() const;
		std::string getLongArg() const;
		void incrementUsageCount();
		void setUsageCount(int count);
		int getUsageCount() const;
		bool getAllowMultyValues() const;

		virtual types::Result<bool> tryParse(std::string& value) = 0;
		virtual types::Result<bool> process(const args_parse::Parser* parser);
	};

	class EmptyArg : public Arg
	{
	public:
		EmptyArg(char shortArg,
		         const std::string& longArg,
		         const std::string& description,
				types::Result<bool>(*process)(const Arg* arg, const args_parse::Parser* parser))
			: Arg(shortArg, longArg, description, process)
		{
			this->canHasValue = false;
		}

		types::Result<bool> tryParse(std::string& value) override;
		types::Result<bool> process(const args_parse::Parser* parser) override;
	};

	class MultyEmptyArg : public EmptyArg
	{
	public:
		MultyEmptyArg(char shortArg,
		              const std::string& longArg,
		              const std::string& description,
			types::Result<bool>(*process)(const Arg* arg, const args_parse::Parser* parser),
			int maxUsageCount = 3)
			: EmptyArg(shortArg, longArg, description, process)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process(const args_parse::Parser* parser) override;
	};

	template<typename T>
	class ValueArg : public Arg
	{
		T value;
		Validator* validator{};
	public:
		ValueArg(char shortArg,
			const std::string& longArg,
			const std::string& description,
			types::Result<bool>(*process)(const Arg* arg, const args_parse::Parser* parser),
			Validator* validator)
			: Arg(shortArg, longArg, description, process)
		{
			this->canHasValue = true;
			this->validator = validator;
		}

		types::Result<bool> tryParse(std::string& value) override
		{
			const types::Result<bool> result = this->validator->validate(value);
			if (!result.data.value()) 
				return { types::ErrorCase("Something went wrong")};

			try
			{
				std::stringstream convert(value);
				convert >> this->value;
				this->hasValue = true;
				return { true };
			}
			catch (const std::invalid_argument&)
			{
				return { false };
			}
			catch (const std::out_of_range&)
			{
				return { false };
			}
		}
		types::Result<bool> process(const args_parse::Parser* parser) override
		{
			std::cout << this->getShortArg() << " " << this->value << std::endl;
			return { true };
		}
	};

	template<typename T>
	class MultyValueArg : public ValueArg<T>
	{
	public:
		MultyValueArg(char shortArg,
			std::string& longArg,
			std::string& description,
			types::Result<bool>(*process)(const Arg* arg, const args_parse::Parser* parser),
			Validator* validator,
			int maxUsageCount = 3)
			: ValueArg<T>(shortArg, longArg, description, process, validator)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process(const args_parse::Parser* parser) override
		{
			std::cout << this->value << " " << this->usageCount << std::endl;
			return { true };
		}
	};
}
