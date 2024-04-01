#pragma once
#include <string>

namespace args
{
	/**
     * \brief Может ли аргумент иметь value
     */
    enum class Status {
        MUST_BE,
        FORBIDDEN
    };

    class Arg 
    {
    private:
        /// Описание аргумента.
        std::string description = "";
    protected:
        char shortArg = ' ';
        std::string longArg = "";
        /// Может ли содержать value.
        Status acceptingTheValue = Status::FORBIDDEN;
        /// Логика без value.
        void (*processFunction)();
        /// Логика с value.
        void (*processWithValueFunction)(std::string value);

    public:  
        Arg(char shortArg, 
            std::string longArg,
            std::string description = "",
            void (*processFunction)() = [](){},
            Status acceptingTheValue = Status::FORBIDDEN, 
            void(*processWithValueFunction)(std::string value) = [](std::string value){});
        Arg(std::string longArg, std::string description, void (*processFunction)(), Status acceptingTheValue,
            void (*processWithValueFunction)(std::string value));
        Arg(char shortArg, std::string longArg, std::string description, void (*processFunction)());
        Arg(char shortArg, std::string longArg, std::string description, void (*processWithValueFunction)(std::string value));

        std::string getDescriptiong() const;
        void setDescription(std::string description);
        char getShortArg() const;
        std::string getLongArg() const;
        Status getAcceptingTheValue() const;
        bool virtual validateValue(std::string value);

        void process();
        void processWithValue(std::string value);
    };
}