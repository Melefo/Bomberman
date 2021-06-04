/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** XMLGenerator
*/

#include "XMLGenerator.hpp"

XMLGenerator::XMLGenerator(const std::string &filepath) : _stream(new std::ofstream), _tags()
{
    _stream->open(filepath);
    this->write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
}

XMLGenerator::~XMLGenerator()
{
    closeFile();
}

/**
 * Public
 */

void XMLGenerator::addTag(const std::string &tagName)
{
    std::string tabs(_tags.size()-1, '\t');

    _tags.push_back(tagName);
    this->write(tabs+"<"+tagName+">");
}

void XMLGenerator::closeAndReopen(const std::string &tagName)
{
    std::string tabs(_tags.size()-1, '\t');

    if (findTag(tagName) >= 0) {
        this->write(tabs+"</"+tagName+">");
        this->write(tabs+"<"+tagName+">");
    }
}

void XMLGenerator::closeLastTag()
{
    std::string tabs(_tags.size()-1, '\t');

    this->write(tabs+"</"+_tags.back()+">");
    _tags.pop_back();
}

void XMLGenerator::closeFile() {
    while (_tags.size() > 0)
        closeLastTag();
    if (_stream->is_open())
        _stream->close();
}

/**
 * Protected
 */

void XMLGenerator::write(const std::string &content)
{
    _stream->write(content.c_str(), content.size());
}

int XMLGenerator::findTag(const std::string &tagName)
{
    int pos = 0;

    for (const auto &it : _tags) {
        if ((*it) == tagName)
            return pos;
        pos++;
    }
    return pos;
}
