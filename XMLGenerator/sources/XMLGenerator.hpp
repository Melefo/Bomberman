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
        XMLGenerator(const std::vector<std::string> &content);
        ~XMLGenerator();

    protected:
        void write(const std::string content);
        void createMap();

        std::unique_ptr<std::ofstream> _stream;
        const std::vector<std::string> &_map;
    private:
};

#endif /* !XMLGENERATOR_HPP_ */
