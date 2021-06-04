/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** testTerrainGenerator
*/

#ifndef TESTTERRAINGENERATOR_HPP_
#define TESTTERRAINGENERATOR_HPP_

#include "TerrainGenerator.hpp"

class TestTerrainGenerator : public TerrainGenerator {
    public:
        TestTerrainGenerator(int playersNbr) : TerrainGenerator(playersNbr, 70) {};
        ~TestTerrainGenerator() = default;

        void trimMap() {TerrainGenerator::trimMap();};
        std::vector<std::string> rotateTile(std::vector<std::string> tile) const {return TerrainGenerator::rotateTile(tile);};
        std::string generateMapLine(int hPos) {return TerrainGenerator::generateMapLine(hPos);};
        void generateBaseMap() {TerrainGenerator::generateBaseMap();};
        void removeBoxes() {
            for (auto &it : _map)
                for (auto &c : it)
                    if (c == 'x')
                        c = ' ';
        };
        bool addTetrOnMap(const std::vector<std::vector<std::string>> &tiles) {return TerrainGenerator::addTetrOnMap(tiles);};
        bool tryPlacingTile(const std::vector<std::string> &tile, int mapPos) {return TerrainGenerator::tryPlacingTile(tile, mapPos);};
        bool tryTetrPositions(const std::vector<std::string> &chosenTile) {return TerrainGenerator::tryTetrPositions(chosenTile);};
        bool blocksPath(int y, int x) {return TerrainGenerator::blocksPath(y,  x);};
        void addTileOnMap(int y, int x) {TerrainGenerator::addTileOnMap(y, x);};
        void placePlayers() {TerrainGenerator::placePlayers();};
        size_t lineGetWidth(int linePos) {return TerrainGenerator::lineGetWidth(linePos);};
        void fillHoles() {TerrainGenerator::fillHoles();};
        bool isMapFull() {return TerrainGenerator::isMapFull();};
        void modifyMap(std::string line, int pos) {_map[pos] = line;};
        int getPlayersNbr() {return _playersNbr;};
};

#endif /* !TESTTERRAINGENERATOR_HPP_ */
