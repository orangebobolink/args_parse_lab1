#pragma once
#include <string>

namespace args_parse
{
    class IValidator {
    public:
        /**
      * \brief Валидирует значение.
      * \param Значение.
      * \return Валидно ли значение.
      */
        virtual bool validateValue(std::string value) = 0;
    };
}