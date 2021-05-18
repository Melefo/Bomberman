/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** testMapper
*/

#include "testMapper.hpp"
#include <criterion/criterion.h>
#include <iostream>

Test(generateMapLine, pair)
{
    TestMapper mapper(6);

    cr_assert_eq(mapper.generateMapLine(4), "W w w w w w w w W");
}

Test(generateMapLine, odd)
{
    TestMapper mapper(6);

    cr_assert_eq(mapper.generateMapLine(5), "W               W");
}

Test(generateBaseMap, five_players)
{
    TestMapper mapper(6);
    int index = 0;
    std::vector<std::string> testMap = {
        "WWWWWWWWWWWWWWWWW",
        "W               W",
        "W w w w w w w w W",
        "W               W",
        "W w w w w w w w W",
        "W               W",
        "W w w w w w w w W",
        "W               W",
        "W w w w w w w w W",
        "W               W",
        "W w w w w w w w W",
        "W               W",
        "WWWWWWWWWWWWWWWWW",
    };

    mapper.removeBoxes();
    cr_assert_eq(13, mapper.getMap().size());
    for (const auto &it : mapper.getMap())
        cr_assert_eq(17, it.length(), "actual = %d\n", it.length());
    for (const auto &it : mapper.getMap()) {
        cr_assert_eq(it, testMap[index], "actual%d = %s\n", index, it.c_str());
        index++;
    }
}
