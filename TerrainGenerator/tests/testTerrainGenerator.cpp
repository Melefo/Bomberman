/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** testTerrainGenerator
*/

#include "testTerrainGenerator.hpp"
#include "OSRedirector.hpp"
#include <iostream>

Test(generateMapLine, pair)
{
    TestTerrainGenerator terrainGenerator(6);

    cr_assert_eq(terrainGenerator.generateMapLine(4), "X o o o o o o o X");
}

Test(generateMapLine, odd)
{
    TestTerrainGenerator terrainGenerator(6);

    cr_assert_eq(terrainGenerator.generateMapLine(5), "X               X");
}

Test(generateBaseMap, six_players_and_sizes)
{
    TestTerrainGenerator terrainGenerator(6);
    int index = 0;
    std::vector<std::string> testMap = {
        "XXXXXXXXXXXXXXXXX",
        "X               X",
        "X o o o o o o o X",
        "X               X",
        "X o o o o o o o X",
        "X               X",
        "X o o o o o o o X",
        "X               X",
        "X o o o o o o o X",
        "X               X",
        "X o o o o o o o X",
        "X               X",
        "XXXXXXXXXXXXXXXXX",
    };

    terrainGenerator.generateBaseMap();
    terrainGenerator.removeBoxes();
    cr_assert_eq(13, terrainGenerator.getMap().size());
    for (const auto &it : terrainGenerator.getMap())
        cr_assert_eq(17, it.length(), "actual = %d\n", it.length());
    for (const auto &it : terrainGenerator.getMap()) {
        cr_assert_eq(it, testMap[index], "actual%d = %s\n", index, it.c_str());
        index++;
    }
}

Test(rotateTile, one_time)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::string> rotatedTile;
    std::vector<std::string> desiredOutput = {
        {"*******"},
        {"*ooooo*"},
        {"***o***"},
        {"xx*o*xx"},
        {"xx***xx"}
    };
    std::vector<std::string> testedTile = {
        {"***xx"},
        {"*o*xx"},
        {"*o***"},
        {"*ooo*"},
        {"*o***"},
        {"*o*xx"},
        {"***xx"}
    };

    rotatedTile = terrainGenerator.rotateTile(testedTile);
    for (size_t i = 0; i < rotatedTile.size(); i++)
        cr_assert_eq(desiredOutput[i], rotatedTile[i]);
}

Test(rotateTile, s_type)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::string> rotatedTile;
    std::vector<std::string> testedTile = {
        {"xx*****"},
        {"xx*ooo*"},
        {"***o***"},
        {"*ooo*xx"},
        {"*****xx"}
    };
    std::vector<std::string> desiredOutput = {
        {"***xx"},
        {"*o*xx"},
        {"*o***"},
        {"*ooo*"},
        {"***o*"},
        {"xx*o*"},
        {"xx***"}
    };

    rotatedTile = terrainGenerator.rotateTile(testedTile);
    for (size_t i = 0; i < rotatedTile.size(); i++)
        cr_assert_eq(desiredOutput[i], rotatedTile[i]);
}

Test(clearMap, basic)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXX"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"XXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    for (size_t i = 0; i < terrainGenerator.getMap().size(); i++)
        cr_assert_eq(terrainGenerator.getMap()[i], desiredOutput[i]);
}

Test(trimMap, basic)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXX"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"XXXXXXXXXXXXXXXXX"},
    };
    std::vector<std::string> secondDesiredOutput = {
        {"XXXXXXXXX"},
        {"X        "},
        {"X        "},
        {"X        "},
        {"X        "},
        {"X        "},
        {"X        "},
        {"X        "},
        {"X        "},
        {"X        "},
        {"X        "},
        {"X        "},
        {"XXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.modifyMap(terrainGenerator.getMap()[4]+std::string("test"), 4);
    for (size_t i = 0; i < terrainGenerator.getMap().size(); i++) {
        if (i == 4)
            cr_assert_eq(terrainGenerator.getMap()[i], desiredOutput[i]+"test");
        else
            cr_assert_eq(terrainGenerator.getMap()[i], desiredOutput[i]);
    }
    terrainGenerator.trimMap();
    for (size_t i = 0; i < terrainGenerator.getMap().size(); i++)
        cr_assert_eq(terrainGenerator.getMap()[i], secondDesiredOutput[i]);
}

Test(addTetrOnMap, basic)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::vector<std::string>> tile = {{
            "x***x",
            "**o**",
            "*ooo*",
            "**o**",
            "x***x"
        },{
            "x***x",
            "**o**",
            "*ooo*",
            "**o**",
            "x***x"
        }
    };
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXX"},
        {"X               X"},
        {"X  o            X"},
        {"X ooo           X"},
        {"X  o            X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"XXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    cr_assert_eq(terrainGenerator.addTetrOnMap(tile), true);
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(tryPlacingTile, basic)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::string> tile = {
        "***xx",
        "*o*xx",
        "*o***",
        "*ooo*",
        "*o***",
        "*o*xx",
        "***xx"
    };
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXX"},
        {"X               X"},
        {"X               X"},
        {"X o             X"},
        {"X o             X"},
        {"X ooo           X"},
        {"X o             X"},
        {"X o             X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"XXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    cr_assert_eq(terrainGenerator.tryPlacingTile(tile, 2), true);
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(tryPlacingTile, one_on_top_another)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::vector<std::string>> tile = {{
            "*****xx",
            "*ooo*xx",
            "***o***",
            "xx*ooo*",
            "xx*****"},{
            "***xx",
            "*o*xx",
            "*o***",
            "*ooo*",
            "*o***",
            "*o*xx",
            "***xx"
        }
    };
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXX"},
        {"X               X"},
        {"X               X"},
        {"X o ooo         X"},
        {"X o   o         X"},
        {"X ooo ooo       X"},
        {"X o             X"},
        {"X o             X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"XXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    cr_expect_eq(terrainGenerator.tryPlacingTile(tile[1], 2), true);
    cr_assert_eq(terrainGenerator.tryPlacingTile(tile[0], 2), true);
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(tryPlacingTile, one_stepping_another)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::vector<std::string>> tile = {{
            "*****xx",
            "*ooo*xx",
            "***o***",
            "xx*ooo*",
            "xx*****"},{
            "***xx",
            "*o*xx",
            "*o***",
            "*ooo*",
            "*o***",
            "*o*xx",
            "***xx"
        }
    };
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXX"},
        {"X               X"},
        {"X   ooo         X"},
        {"X o   o         X"},
        {"X o   ooo       X"},
        {"X ooo           X"},
        {"X o             X"},
        {"X o             X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"XXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    cr_expect_eq(terrainGenerator.tryPlacingTile(tile[1], 2), true);
    cr_assert_eq(terrainGenerator.tryPlacingTile(tile[0], 1), true);
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(tryTetrPositions, basic)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::vector<std::string>> tile = {{
            "*****xx",
            "*ooo*xx",
            "***o***",
            "xx*ooo*",
            "xx*****"},{
            "***",
            "*o*",
            "***"
        }
    };
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXX"},
        {"X               X"},
        {"X   ooo ooo     X"},
        {"X o   o         X"},
        {"X o   ooo       X"},
        {"X ooo           X"},
        {"X o    ooo      X"},
        {"X o  o   o      X"},
        {"X   ooo  ooo    X"},
        {"X    o          X"},
        {"X      ooo      X"},
        {"X               X"},
        {"XXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    for (size_t pos = 0; pos != desiredOutput.size(); pos++)
        terrainGenerator.modifyMap(desiredOutput[pos], pos);
    cr_expect_eq(terrainGenerator.tryTetrPositions(tile[0]), false);
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
    cr_expect_eq(terrainGenerator.tryTetrPositions(tile[1]), true);
    cr_assert_neq(terrainGenerator.getMap(), desiredOutput);
}

Test(blocksPath, basic)
{
    TestTerrainGenerator terrainGenerator(6);

    terrainGenerator.generateBaseMap();
    cr_assert_eq(terrainGenerator.blocksPath(3, 3), true);
    cr_assert_eq(terrainGenerator.blocksPath(3, 2), true);
    cr_assert_eq(terrainGenerator.blocksPath(1, 1), true);
    terrainGenerator.clearMap();
    terrainGenerator.modifyMap("X o             X", 2);
    terrainGenerator.modifyMap("X   o           X", 4);
    cr_assert_eq(terrainGenerator.blocksPath(3, 3), false);
    cr_assert_eq(terrainGenerator.blocksPath(3, 6), false);
}

Test(displayMap, basic)
{
    TestTerrainGenerator terrainGenerator(6);
    std::string desiredOutput =
        std::string("XXXXXXXXXXXXXXXXX\n")+
        std::string("X               X\n")+
        std::string("X o o o o o o o X\n")+
        std::string("X               X\n")+
        std::string("X o o o o o o o X\n")+
        std::string("X               X\n")+
        std::string("X o o o o o o o X\n")+
        std::string("X               X\n")+
        std::string("X o o o o o o o X\n")+
        std::string("X               X\n")+
        std::string("X o o o o o o o X\n")+
        std::string("X               X\n")+
        std::string("XXXXXXXXXXXXXXXXX\n");
    std::string content;

    terrainGenerator.generateBaseMap();
    terrainGenerator.removeBoxes();
    OSRedirector os(std::cout);
    terrainGenerator.displayMap();
    content = os.getContent();
    cr_assert_eq(content, desiredOutput, "actual = %s\nshould = %s\n", content.c_str(), desiredOutput.c_str());
}

Test(addTileOnMap, basic)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXX"},
        {"X               X"},
        {"X  o            X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"XXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.addTileOnMap(2, 3);
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(placePlayers, two_players)
{
    TestTerrainGenerator terrainGenerator(2);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXX"},
        {"XP          X"},
        {"X           X"},
        {"X           X"},
        {"X           X"},
        {"X           X"},
        {"X           X"},
        {"X           X"},
        {"X           X"},
        {"X           X"},
        {"X           X"},
        {"X          PX"},
        {"XXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.placePlayers();
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(placePlayers, three_players)
{
    TestTerrainGenerator terrainGenerator(3);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXX"},
        {"XP           PX"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"XP           PX"},
        {"XXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.placePlayers();
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(placePlayers, four_players)
{
    TestTerrainGenerator terrainGenerator(4);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXX"},
        {"XP           PX"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"XP           PX"},
        {"XXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.placePlayers();
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(placePlayers, six_players)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXX"},
        {"XP      P      PX"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"X               X"},
        {"XP      P      PX"},
        {"XXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.placePlayers();
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(placePlayers, eight_players)
{
    TestTerrainGenerator terrainGenerator(8);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXXXX"},
        {"XP       P       PX"},
        {"X                 X"},
        {"X                 X"},
        {"X                 X"},
        {"X                 X"},
        {"XP               PX"},
        {"X                 X"},
        {"X                 X"},
        {"X                 X"},
        {"X                 X"},
        {"XP       P       PX"},
        {"XXXXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.placePlayers();
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(placePlayers, more_players)
{
    TestTerrainGenerator terrainGenerator(22);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXXXXXX"},
        {"XP       P       PX"},
        {"X                 X"},
        {"X                 X"},
        {"X                 X"},
        {"X                 X"},
        {"XP               PX"},
        {"X                 X"},
        {"X                 X"},
        {"X                 X"},
        {"X                 X"},
        {"XP       P       PX"},
        {"XXXXXXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.placePlayers();
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(blocksPath, advanced)
{
    TestTerrainGenerator terrainGenerator(4);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXX"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X             X"},
        {"X     o o     X"},
        {"X             X"},
        {"X     o o     X"},
        {"X             X"},
        {"XXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    cr_assert_eq(terrainGenerator.blocksPath(5, 6), false);
    terrainGenerator.modifyMap("X     o o     X", 8);
    terrainGenerator.modifyMap("X     o o     X", 10);
    cr_assert_eq(terrainGenerator.blocksPath(9, 7), true);
    terrainGenerator.modifyMap("X     ooo     X", 7);
    cr_assert_eq(terrainGenerator.blocksPath(9, 7), true);
    terrainGenerator.modifyMap("X     ooo     X", 8);
    cr_assert_eq(terrainGenerator.blocksPath(9, 7), true);
    terrainGenerator.modifyMap("X     ooo     X", 9);
    cr_assert_eq(terrainGenerator.blocksPath(9, 7), true);
    terrainGenerator.modifyMap("X     oo      X", 9);
    cr_assert_eq(terrainGenerator.blocksPath(9, 7), true);
}

Test(lineGetWidth, basic)
{
    TestTerrainGenerator terrainGenerator(4);

    terrainGenerator.clearMap();
    terrainGenerator.modifyMap("X       o     X", 1);
    cr_assert_eq(terrainGenerator.lineGetWidth(1), 9);
    terrainGenerator.modifyMap("Xo            X", 2);
    cr_assert_eq(terrainGenerator.lineGetWidth(2), 2);
    terrainGenerator.modifyMap("X            oX", 3);
    cr_assert_eq(terrainGenerator.lineGetWidth(3), 14);
    cr_assert_eq(terrainGenerator.lineGetWidth(4), 1);
}

Test(fillHoles, basic)
{
    TestTerrainGenerator terrainGenerator(4);
    std::vector<std::string> desiredOutput = {
        {"XXXXXXXXXXXXXXX"},
        {"Xoooooooooooo X"},
        {"Xoooooooooooo X"},
        {"Xoooooooooooo X"},
        {"Xoooooooooooo X"},
        {"Xoooooooooooo X"},
        {"Xoooooooooooo X"},
        {"Xoooooooooooo X"},
        {"Xoooooooooooo X"},
        {"Xoooooooooooo X"},
        {"Xoooooooooooo X"},
        {"X             X"},
        {"XXXXXXXXXXXXXXX"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.fillHoles();
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
}

Test(isMapFull, basic)
{
    TestTerrainGenerator terrainGenerator(4);

    terrainGenerator.clearMap();
    terrainGenerator.modifyMap("Xoooooooooooo X", 1);
    terrainGenerator.modifyMap("Xoooooooooooo X", 2);
    terrainGenerator.modifyMap("Xoooooooooooo X", 3);
    terrainGenerator.modifyMap("Xoooooooooooo X", 4);
    terrainGenerator.modifyMap("Xoooooooooooo X", 5);
    cr_assert_eq(terrainGenerator.isMapFull(), false);
    terrainGenerator.modifyMap("Xoooooooooooo X", 6);
    cr_assert_eq(terrainGenerator.isMapFull(), true);
    terrainGenerator.modifyMap("Xooooo        X", 3);
    cr_assert_eq(terrainGenerator.isMapFull(), false);
}

Test(generateRandomMap, seed_test)
{
    TestTerrainGenerator terrainGenerator(4);
    std::vector<std::string> firstOutput;

    terrainGenerator.generateRandomMap(8);
    firstOutput = terrainGenerator.getMap();
    terrainGenerator.generateRandomMap(8);
    cr_assert_eq(terrainGenerator.getMap(), firstOutput);
}
