/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** XMLGenerator
*/

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "XMLGenerator.hpp"

XMLGenerator::XMLGenerator(const std::vector<std::string> &content, const std::string &filepath) : _stream(new std::ofstream), _map(content)
{
    _stream->open(filepath);
    this->write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    this->write("<Map>\n");
    createMap();
    this->write("</Map>\n");
    _stream->close();
}

XMLGenerator::~XMLGenerator()
{
}

void XMLGenerator::write(const std::string content)
{
    _stream->write(content.c_str(), content.size());
}

void XMLGenerator::createMap()
{
    this->write(std::string("<OPERATOR TYPE=\"IN\"/>\n<OPERAND>\n\t<LIST>\n"));
    for (const auto &it : _map) {
        this->write(std::string("\t\t<LITERAL VALUE=\""+it+"\"/>\n"));
    }
    this->write("\t<LIST>\n</OPERAND>\n");
}