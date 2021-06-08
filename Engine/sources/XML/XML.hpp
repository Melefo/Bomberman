/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** XML
*/

#ifndef XML_HPP_
#define XML_HPP_

#include <string>
#include <exception>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Coordinator.hpp"

class XMLException : public std::exception
{
    private:
        std::string _value;
    public:
        XMLException(std::string value);
        const char *what() const noexcept override;
};

class XML
{
    private:
        static void CreateWall(ECS::Entity& entity, boost::property_tree::ptree& xml);
        static void CreatePlayer(ECS::Entity& entity, boost::property_tree::ptree& xml);
    public:
        XML() = delete;
        ~XML() = delete;

    static void LoadMap(std::string path, ECS::Coordinator& coordinator);
};

#endif /* !XML_HPP_ */
