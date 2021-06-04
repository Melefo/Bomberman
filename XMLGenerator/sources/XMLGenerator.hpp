/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** XMLGenerator
*/

#ifndef XMLGENERATOR_HPP_
#define XMLGENERATOR_HPP_

#include <fstream>
#include <memory>
#include <vector>
#include <string>

class XMLGenerator {
    public:
        /**
         * @brief Construct a new XMLGenerator object
         * 
         * @param filepath The file to save in
         */
        XMLGenerator(const std::string &filepath = "save.xml");
        /**
         * @brief Destroy the XMLGenerator object
         * 
         */
        ~XMLGenerator();

        /**
         * @brief Add a tag to the file
         * 
         * @param tagName The tag name
         */
        void addTag(const std::string &tagName);
        /**
         * @brief Close and reopen a tag
         * Does nothing if the tag does not exists
         * 
         * @param tagName The tag name
         */
        void closeAndReopen(const std::string &tagName);
        /**
         * @brief Close the last tag added
         * 
         */
        void closeLastTag();
        /**
         * @brief Close the file stream and closes all unclosed tags
         * 
         */
        void closeFile();
        /**
         * @brief Add some content to the file
         * 
         * @param content The content to add
         */
        void write(const std::string &content);
        /**
         * @brief Add tagged value
         * 
         * @param name Tag name
         * @param value Value to write
         */
        void addValue(const std::string &name, int value);
    protected:
        /**
         * @brief Find the position of the given tag in the class vector
         * Returns -1 if not found
         * 
         * @param tagName The tag to search
         * @return int The tag position in the class vector
         */
        int findTag(const std::string &tagName);

        /**
         * @brief The file's ofstream
         * 
         */
        std::unique_ptr<std::ofstream> _stream;
        /**
         * @brief The added tags to the file
         * 
         */
        std::vector<std::string> _tags;
};

#endif /* !XMLGENERATOR_HPP_ */
