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

Test(addTag, basic)
{
    std::string filepath = "./test1createMap.xml";
    TestXMLGenerator xmlFile(filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Soupe>\n")+
        std::string("\t<Ingredients>\n")+
        std::string("\t\t<Carotte>\n")+
        std::string("\t\t</Carotte>\n")+
        std::string("\t</Ingredients>\n")+
        std::string("</Soupe>\n");
    xmlFile.addTag("Soupe");
    xmlFile.addTag("Ingredients");
    xmlFile.addTag("Carotte");
    xmlFile.closeFile();

    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    //cr_assert_eq(remove(filepath.c_str()), 0);
}

Test(closeAndReopen, basic)
{
    std::string filepath = "test2createMap.xml";
    TestXMLGenerator xmlFile(filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Soupe>\n")+
        std::string("\t<Ingredients>\n")+
        std::string("\t\t<Carotte>\n")+
        std::string("\t\t</Carotte>\n")+
        std::string("\t</Ingredients>\n")+
        std::string("\t<Ingredients>\n")+
        std::string("\t\t<Patate>\n")+
        std::string("\t\t</Patate>\n")+
        std::string("\t</Ingredients>\n")+
        std::string("</Soupe>\n");
    xmlFile.addTag("Soupe");
    xmlFile.addTag("Ingredients");
    xmlFile.addTag("Carotte");
    xmlFile.closeLastTag();
    xmlFile.closeAndReopen("Ingredients");
    xmlFile.addTag("Patate");
    xmlFile.closeAndReopen("Ravioli");
    xmlFile.closeFile();
    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    cr_assert_eq(remove(filepath.c_str()), 0);
}

Test(closeLastTag, basic)
{
    std::string filepath = "test3createMap.xml";
    TestXMLGenerator xmlFile(filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Soupe>\n")+
        std::string("\t<Ingredients>\n")+
        std::string("\t</Ingredients>\n")+
        std::string("\t<Carotte>\n")+
        std::string("\t</Carotte>\n")+
        std::string("</Soupe>\n");
    xmlFile.addTag("Soupe");
    xmlFile.addTag("Ingredients");
    xmlFile.closeLastTag();
    xmlFile.addTag("Carotte");
    xmlFile.closeFile();
    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    cr_assert_eq(remove(filepath.c_str()), 0);
}

Test(closeFile, basic)
{
    std::string filepath = "test4createMap.xml";
    TestXMLGenerator xmlFile(filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Soupe>\n")+
        std::string("\t<Ingredients>\n")+
        std::string("\t\t<Carotte>\n")+
        std::string("\t\t\t<Orange>\n")+
        std::string("\t\t\t</Orange>\n")+
        std::string("\t\t</Carotte>\n")+
        std::string("\t</Ingredients>\n")+
        std::string("</Soupe>\n");
    xmlFile.addTag("Soupe");
    xmlFile.addTag("Ingredients");
    xmlFile.addTag("Carotte");
    xmlFile.addTag("Orange");
    xmlFile.closeFile();
    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    cr_assert_eq(remove(filepath.c_str()), 0);
}

Test(write, basic)
{
    std::string filepath = "test5createMap.xml";
    TestXMLGenerator xmlFile(filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Soupe>\n")+
        std::string("\t<Ingredients>\n")+
        std::string("\t\t<Carotte>\n")+
        std::string("Vert")+
        std::string("\t\t</Carotte>\n")+
        std::string("\t</Ingredients>\n")+
        std::string("</Soupe>\n");
    xmlFile.addTag("Soupe");
    xmlFile.addTag("Ingredients");
    xmlFile.addTag("Carotte");
    xmlFile.write("Vert");
    xmlFile.closeFile();
    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    cr_assert_eq(remove(filepath.c_str()), 0);
}

Test(addValue, basic)
{
    std::string filepath = "test6createMap.xml";
    TestXMLGenerator xmlFile(filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Soupe>\n")+
        std::string("\t<Ingredients>\n")+
        std::string("\t\t<Carotte>1</Carotte>\n")+
        std::string("\t\t<Poulet>1</Poulet>\n")+
        std::string("\t\t<Patate>2</Patate>\n")+
        std::string("\t</Ingredients>\n")+
        std::string("</Soupe>\n");
    xmlFile.addTag("Soupe");
    xmlFile.addTag("Ingredients");
    xmlFile.addValue("Carotte", 1);
    xmlFile.addValue("Poulet", 1);
    xmlFile.addValue("Patate", 2);
    xmlFile.closeFile();
    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    cr_assert_eq(remove(filepath.c_str()), 0);
}
