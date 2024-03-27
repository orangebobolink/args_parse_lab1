#pragma once
#include <string>

using namespace std;

namespace args_parse
{

	/**
     * \brief Может ли аргумент иметь value
     */
    enum class Status {
        MUST_BE,
        MAYBE,
        FORBIDDEN
    };

    class Arg  
    {
    private:
        /// Описание аргумента.
        string description = "";
    protected:
        char shortArg = ' ';
        string longArg = "";
        /// Может ли содержать value.
        Status acceptingTheValue = Status::FORBIDDEN;
        /// Логика без value.
        void (*processFunction)();
        /// Логика с value.
        void (*processWithValueFunction)(string value);

        /**
         * \brief Валидирует значение.
         * \param Значение.
         * \return Валидно ли значение.
         */
        virtual bool validationValue(string value);

    public:  
        explicit Arg(char shortArg, 
            string longArg,
            string description = "", 
            void (*processFunction)() = [](){},
            Status acceptingTheValue = Status::FORBIDDEN, 
            void(*processWithValueFunction)(string value) = [](string value){});
        Arg(string longArg, string description, void (*processFunction)(), Status acceptingTheValue,
            void (*processWithValueFunction)(string value));
        Arg(char shortArg, string longArg, string description, void (*processFunction)());
        Arg(char shortArg, string longArg, string description, void (*processWithValueFunction)(string value));

        ~Arg();

        string getDescriptiong();
        void setDescription(string description);
        char getShortArg();
        string getLongArg();
        Status getAcceptingTheValue();

        void process();
        void processWithValue(string value);
    };
}