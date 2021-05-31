/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** testXMLGenerator
*/

#include "testXMLGenerator.hpp"
#include <iostream>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <cstdio>

Test(write, basic)
{
    std::vector<std::string> empty;
    std::string filepath = "test1write.xml";
    TestXMLGenerator xmlFile(empty, filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Map>\n")+
        std::string("<OPERATOR TYPE=\"IN\"/>\n<OPERAND>\n\t<LIST>\n")+
        std::string("\t<LIST>\n</OPERAND>\n")+
        std::string("</Map>\n");
    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    xmlFile.write(std::string("This is a test."));
    stream.open(filepath);
    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    stream.close();
    cr_expect_eq(output, desiredOutput+std::string("This is a test."));
    cr_assert_eq(remove(filepath.c_str()), 0);
}

Test(createMap, empty)
{
    std::vector<std::string> empty;
    std::string filepath = "test2createMap.xml";
    TestXMLGenerator xmlFile(empty, filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Map>\n")+
        std::string("<OPERATOR TYPE=\"IN\"/>\n<OPERAND>\n\t<LIST>\n")+
        std::string("\t<LIST>\n</OPERAND>\n")+
        std::string("</Map>\n");
    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    cr_assert_eq(remove(filepath.c_str()), 0);
}

Test(createMap, not_empty)
{
    std::vector<std::string> full = {
        "Hello",
        "World",
        "!"
    };
    std::string filepath = "test3createMap.xml";
    TestXMLGenerator xmlFile(full, filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Map>\n")+
        std::string("<OPERATOR TYPE=\"IN\"/>\n<OPERAND>\n\t<LIST>\n")+
        std::string("\t\t<LITERAL VALUE=\"Hello\"/>\n")+
        std::string("\t\t<LITERAL VALUE=\"World\"/>\n")+
        std::string("\t\t<LITERAL VALUE=\"!\"/>\n")+
        std::string("\t<LIST>\n</OPERAND>\n")+
        std::string("</Map>\n");
    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    cr_assert_eq(remove(filepath.c_str()), 0);
}
