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

	class EmptyArg : public Arg
	{
	public:
		EmptyArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*processFunction)())
			: Arg(shortArg, longArg, description, processFunction)
		{
			this->hasValue = false;
		}

		bool validateValue(std::string value) override;
		types::Result<bool> process() override;
	};

	class ValueArg : public Arg
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

	class StringArg : public ValueArg
	{
	public:
		StringArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)())
			: ValueArg(shortArg, longArg, description, process) {}

		bool validateValue(std::string value) override;
	};

	class IntArg : public ValueArg
	{
	public:
		IntArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)())
			: ValueArg(shortArg, longArg, description, process) {}


		bool validateValue(std::string value) override;
	};

	class BoolArg : public ValueArg
	{
	public:
		BoolArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)())
			: ValueArg(shortArg, longArg, description, process) {}


		bool validateValue(std::string value) override;
	};

	class MultyEmptyArg : public args::EmptyArg
	{
	public:
		MultyEmptyArg(char shortArg,
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

	class MultyIntArg : public args::IntArg
	{
	public:
		MultyIntArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(),
			int maxUsageCount = 3)
			: IntArg(shortArg, longArg, description, process)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process() override;
	};

	class MultyStringlArg : public args::StringArg
	{
	public:
		MultyStringlArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(),
			int maxUsageCount = 3)
			: StringArg(shortArg, longArg, description, process)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process() override;
	};

	class MultyBoolArg : public args::BoolArg
	{
	public:
		MultyBoolArg(char shortArg,
			std::string longArg,
			std::string description,
			types::Result<bool>(*process)(),
			int maxUsageCount = 3)
			: BoolArg(shortArg, longArg, description, process)
		{
			this->allowMultyValues = true;
			this->maxUsageCount = maxUsageCount;
		}

		types::Result<bool> process() override;
	};
}