#pragma once
#include "arg.hpp"
#include <vector> 
#include <tuple>

using namespace std;

namespace args_parse
{
	enum class OperatorType
	{
		LONG,
		SHORT,
		NOPE
	};

	class Parser
	{
	private:
		int argc = 0;
		const char** argv;
		vector<Arg> args;
		OperatorType isOperator(string str);
		Arg findLongOperator(string item, string& value);
		Arg findShortOperator(string item, string& value);
		tuple<Arg, string> getOperator(string item, OperatorType operatorType);
	public:
		explicit Parser(int argc,
			const char** argv);
		~Parser();

		bool parse();
		void addArg(Arg arg);
	};
}