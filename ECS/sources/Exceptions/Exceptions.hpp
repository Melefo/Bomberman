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

namespace ECS::Exception
{
    class SystemManagerException : public std::exception
    {
        private:
            std::string _value;
        public:
            SystemManagerException(std::string value);
            const char *what() const noexcept override;
    };

    class EntityManagerException : public std::exception
    {
        private:
            std::string _value;
        public:
            EntityManagerException(std::string value);
            const char *what() const noexcept override;
    };

    class EntityException : public std::exception
    {
        private:
            std::string _value;
        public:
            EntityException(std::string value);
            const char *what() const noexcept override;
    };
}
#endif /* !EXCEPTIONS_HPP_ */
