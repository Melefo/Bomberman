/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Exceptions
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <exception>
#include <string>

namespace Lua::Exception
{
    /**
     * @brief Exception thrown if the TableValue have an expected behavior
     * 
     */
    class TableValueException : public std::exception
    {
        private:
            std::string _value;
        public:
            TableValueException(std::string value);
            const char *what() const noexcept override;
    };
};

#endif /* !EXCEPTIONS_HPP_ */
