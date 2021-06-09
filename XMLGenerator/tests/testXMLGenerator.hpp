/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** testXMLGenerator
*/

#ifndef TESTXMLGENERATOR_HPP_
#define TESTXMLGENERATOR_HPP_

#include "XMLGenerator.hpp"

class TestXMLGenerator : public XMLGenerator {
    public:
        TestXMLGenerator(const std::string &filepath) : XMLGenerator(filepath), _filepath(filepath) {};
        ~TestXMLGenerator() = default;

    protected:
        std::string _filepath;
};

#endif /* !TESTXMLGENERATOR_HPP_ */
