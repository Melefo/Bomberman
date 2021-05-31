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
        TestXMLGenerator(const std::vector<std::string> &content, const std::string &filepath) : XMLGenerator(content, filepath), _filepath(filepath) {};
        ~TestXMLGenerator() = default;

        void write(const std::string content) {
            _stream->open(_filepath, std::ios::app);
            XMLGenerator::write(content);
            _stream->close();
        };
    protected:
        std::string _filepath;
};

#endif /* !TESTXMLGENERATOR_HPP_ */
