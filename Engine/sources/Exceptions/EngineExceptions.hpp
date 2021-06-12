/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** EngineExceptions
*/

#ifndef ENGINEEXCEPTIONS_HPP_
#define ENGINEEXCEPTIONS_HPP_

#include <exception>
#include <string>

namespace Engine::Exception
{
    /**
     * @brief Exception thrown if the Asset have an expected behavior
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
     * @brief Exception thrown if something in the engine has expected behavior
     * 
     */
    class EngineException : public std::exception
    {
        private:
            std::string _value;
        public:
            EngineException(std::string value);
            const char *what() const noexcept override;
    };
}

#endif /* !ENGINEEXCEPTIONS_HPP_ */
