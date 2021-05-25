/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** testTerrainGenerator
*/

#include "testTerrainGenerator.hpp"
#include <criterion/criterion.h>
#include <iostream>

Test(generateMapLine, pair)
{
    TestTerrainGenerator terrainGenerator(6);

    cr_assert_eq(terrainGenerator.generateMapLine(4), "O o o o o o o o O");
}

Test(generateMapLine, odd)
{
    TestTerrainGenerator terrainGenerator(6);

    cr_assert_eq(terrainGenerator.generateMapLine(5), "O               O");
}

Test(generateBaseMap, six_players_and_sizes)
{
    TestTerrainGenerator terrainGenerator(6);
    int index = 0;
    std::vector<std::string> testMap = {
        "OOOOOOOOOOOOOOOOO",
        "O               O",
        "O o o o o o o o O",
        "O               O",
        "O o o o o o o o O",
        "O               O",
        "O o o o o o o o O",
        "O               O",
        "O o o o o o o o O",
        "O               O",
        "O o o o o o o o O",
        "O               O",
        "OOOOOOOOOOOOOOOOO",
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
        {"OOOOOOOOOOOOOOOOO"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"OOOOOOOOOOOOOOOOO"},
    };

    terrainGenerator.clearMap();
    for (size_t i = 0; i < terrainGenerator.getMap().size(); i++)
        cr_assert_eq(terrainGenerator.getMap()[i], desiredOutput[i]);
}

Test(trimMap, basic)
{
    TestTerrainGenerator terrainGenerator(6);
    std::vector<std::string> desiredOutput = {
        {"OOOOOOOOOOOOOOOOO"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"OOOOOOOOOOOOOOOOO"},
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
        cr_assert_eq(terrainGenerator.getMap()[i], desiredOutput[i]);
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
        {"OOOOOOOOOOOOOOOOO"},
        {"O               O"},
        {"O  o            O"},
        {"O ooo           O"},
        {"O  o            O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"OOOOOOOOOOOOOOOOO"},
    };

    terrainGenerator.clearMap();
    terrainGenerator.addTetrOnMap(tile);
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
        {"OOOOOOOOOOOOOOOOO"},
        {"O               O"},
        {"O               O"},
        {"O o             O"},
        {"O o             O"},
        {"O ooo           O"},
        {"O o             O"},
        {"O o             O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"OOOOOOOOOOOOOOOOO"},
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
        {"OOOOOOOOOOOOOOOOO"},
        {"O               O"},
        {"O               O"},
        {"O o ooo         O"},
        {"O o   o         O"},
        {"O ooo ooo       O"},
        {"O o             O"},
        {"O o             O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"OOOOOOOOOOOOOOOOO"},
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
        {"OOOOOOOOOOOOOOOOO"},
        {"O               O"},
        {"O   ooo         O"},
        {"O o   o         O"},
        {"O o   ooo       O"},
        {"O ooo           O"},
        {"O o             O"},
        {"O o             O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"O               O"},
        {"OOOOOOOOOOOOOOOOO"},
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
        {"OOOOOOOOOOOOOOOOO"},
        {"O               O"},
        {"O   ooo ooo     O"},
        {"O o   o         O"},
        {"O o   ooo       O"},
        {"O ooo           O"},
        {"O o    ooo      O"},
        {"O o  o   o      O"},
        {"O   ooo  ooo    O"},
        {"O    o          O"},
        {"O      ooo      O"},
        {"O               O"},
        {"OOOOOOOOOOOOOOOOO"},
    };

    terrainGenerator.clearMap();
    for (size_t pos = 0; pos != desiredOutput.size(); pos++)
        terrainGenerator.modifyMap(desiredOutput[pos], pos);
    cr_expect_eq(terrainGenerator.tryTetrPositions(tile[0]), false);
    cr_assert_eq(terrainGenerator.getMap(), desiredOutput);
    cr_expect_eq(terrainGenerator.tryTetrPositions(tile[1]), true);
    cr_assert_neq(terrainGenerator.getMap(), desiredOutput);
}
