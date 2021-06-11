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

/**
 * @brief List of exceptions used inside the ECS
 * 
 */
namespace ECS::Exception
{
    /**
     * @brief Exception thrown if the AssetManager have an expected behavior
     * 
     */
    class AssetException : public std::exception
    {
        private:
            std::string _value;
        public:
            AssetException(std::string value);
            const char *what() const noexcept override;
    };

    /**
     * @brief Exception thrown if the AssetManager have an expected behavior
     * 
     */
    class AssetManagerException : public std::exception
    {
        private:
            std::string _value;
        public:
            AssetManagerException(std::string value);
            const char *what() const noexcept override;
    };
    
    /**
     * @brief Exception thrown if the SystemManager have an expected behavior
     * 
     */
    class SystemManagerException : public std::exception
    {
        private:
            std::string _value;
        public:
            SystemManagerException(std::string value);
            const char *what() const noexcept override;
    };

    /**
     * @brief Exception thrown if the EntityManager have an expected behavior
     * 
     */
    class EntityManagerException : public std::exception
    {
        private:
            std::string _value;
        public:
            EntityManagerException(std::string value);
            const char *what() const noexcept override;
    };

    /**
     * @brief Exception thrown if an Entity have an expected behavior
     * 
     */
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
