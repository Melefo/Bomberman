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
    size_t tagsSize = _tags.size() > 0 ? _tags.size() : 0;
    std::string tabs(tagsSize, '\t');

    _tags.push_back(tagName);
    this->write(tabs+"<"+tagName+">\n");
}

void XMLGenerator::closeAndReopen(const std::string &tagName)
{
    size_t tagsSize = _tags.size() > 0 ? _tags.size()-1 : 0;
    std::string tabs(tagsSize, '\t');
    size_t position = 0;

    if ((position = findTag(tagName) >= 0)) {
        for (; _tags.size()-1 > position; closeLastTag());
        this->write(tabs+"</"+tagName+">\n");
        this->write(tabs+"<"+tagName+">\n");
    }
}

void XMLGenerator::closeLastTag()
{
    size_t tagsSize = _tags.size() > 0 ? _tags.size()-1 : 0;
    std::string tabs(tagsSize, '\t');

    this->write(tabs+"</"+_tags.back()+">\n");
    _tags.pop_back();
}

void XMLGenerator::closeFile() {
    while (_tags.size() > 0)
        closeLastTag();
    if (_stream->is_open())
        _stream->close();
}

void XMLGenerator::write(const std::string &content)
{
    _stream->write(content.c_str(), content.size());
}

void XMLGenerator::addValue(const std::string &name, int value)
{
    size_t tagsSize = _tags.size() > 0 ? _tags.size() : 0;
    std::string tabs(tagsSize, '\t');

    this->write(tabs+"<"+name+">"+std::to_string(value)+"</"+name+">\n");
}

/**
 * Protected
 */

int XMLGenerator::findTag(const std::string &tagName)
{
    int pos = -1;

    for (const auto &it : _tags) {
        if (it == tagName)
            return pos+1;
        pos++;
    }
    return -1;
}
