#pragma once
#include "arg.hpp"
#include <vector> 

using namespace std;

namespace args_parse
{
    enum class OperatorType
    {
		LONG,
        SHORT,
        NOPE
    };

    class Parcer
    {
    private:
        int argc = 0;
        const char** argv;
        vector<Arg> args;
        OperatorType isOperator(string str);
        Arg findLongOperator(string item);
        Arg findShortOperator(char item);
        Arg getOperator(string item, OperatorType operatorType);
    public:
        explicit Parcer(int argc,
            const char** argv);
        ~Parcer();

        bool parce();
        void addArg(Arg arg);
    };
}