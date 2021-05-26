/*
** EPITECH PROJECT, 2021
** temp
** File description:
** TerrainGenerator
*/

#include "TerrainGenerator.hpp"
#include <map>
#include <cstdlib>
#include <algorithm>

#include <iostream>

TerrainGenerator::TerrainGenerator(int playersNbr, int boxPercentage)
    : _playersNbr(playersNbr % 2 == 0 ? playersNbr : playersNbr+1), _boxPercentage(boxPercentage),
    _height(13)
{
    std::map<int, int> mapSizes = {
        {2, 13},
        {4, 15},
        {6, 17},
        {8, 19}
    };

    _width = mapSizes[_playersNbr];
    _map = std::vector<std::string>(_height);
    generateMap();
}

TerrainGenerator::~TerrainGenerator()
{
}

/**
 * Getters
 */

std::vector<std::string> TerrainGenerator::getMap() const
{
    return _map;
}

/**
 * Public
 */

void TerrainGenerator::displayMap()
{
    for (auto it = _map.begin(); it != _map.end(); it++)
        std::cout << *it << std::endl;
}

void TerrainGenerator::generateBaseMap()
{
    int index = 0;

    clearMap();
    for (; index < _height; index++)
        _map[index] = std::string(_width, mapTexture::OWALL);
    index = 0;
    for (auto &it : _map) {
        if (index == 0 || index == _height - 1)
            it = std::string(_width, mapTexture::OWALL);
        else
            it = generateMapLine(index);
        index++;
    }
}

void TerrainGenerator::generateRandomMap()
{
    int index = 0;
    std::vector<std::vector<std::string>> tiles = {
        {
            {"***xx"},
            {"*o*xx"},
            {"*o***"},
            {"*ooo*"},
            {"*o***"},
            {"*o*xx"},
            {"***xx"}
        },{
            {"******"},
            {"*oooo*"},
            {"*o****"},
            {"*o*xxx"},
            {"***xxx"}
        },{
            {"x***x"},
            {"**o**"},
            {"*ooo*"},
            {"**o**"},
            {"x***x"}
        },{
            {"*****xx"},
            {"*ooo*xx"},
            {"***o***"},
            {"xx*ooo*"},
            {"xx*****"}
        },{
            {"***"},
            {"*o*"},
            {"*o*"},
            {"*o*"},
            {"***"}
        }
    };

    for (auto &it : _map) {
        it.clear();
        if (index == 0 || index == _height-1)
            it = std::string(_width, mapTexture::OWALL);
        else {
            it = mapTexture::OWALL;
            it += std::string(_width-2, ' ');
            it += mapTexture::OWALL;
        }
        index++;
    }
    while (!isMapFull()) {
        if (!addTetrOnMap(tiles))
            break;
    }
    //fillHoles();
    trimMap();
    cloneReverseMap();
}

void TerrainGenerator::clearMap()
{
    int index = 0;

    for (auto &it : _map) {
        it.clear();
        if (index == 0 || index == _height-1) {
            it = std::string(_width, mapTexture::OWALL);
        } else {
            it += mapTexture::OWALL;
            it += std::string(_width-2, ' ');
            it += mapTexture::OWALL;
        }
        index++;
    }
}

void TerrainGenerator::addTileOnMap(int y, int x)
{
    _map[y][x] = mapTexture::INWALL;
}

/**
 * Private
 */

void TerrainGenerator::placePlayers()
{
    _map[1][1] = 'P';
    _map[_height-2][_width-2] = 'P';
    if (_playersNbr > 2) {
        _map[1][_width-2] = 'P';
        _map[_height-2][1] = 'P';
    }
    if (_playersNbr > 4) {
        _map[1][_width/2] = 'P';
        _map[_height-2][_width/2] = 'P';
    }
    if (_playersNbr > 6) {
        _map[_height/2][1] = 'P';
        _map[_height/2][_width-2] = 'P';
    }
}

void TerrainGenerator::generateBoxes()
{
    for (std::vector<std::string>::iterator it = _map.begin()+1; it != _map.end()-1; it++) {
        for (std::size_t index = 1; index != it->length()-1; index++) {
            if ((*it)[index] == ' ') 
                (*it)[index] = rand() % 100+1 < _boxPercentage ? 'x' : ' ';
        }
    }
}

void TerrainGenerator::generateMap()
{
    srand (static_cast<unsigned int>(time(NULL)));

    if (rand() % 3 == 0)
        generateBaseMap();
    else
        generateRandomMap();
    generateBoxes();
    placePlayers();
}

/**
 * Private - Basic Map
 */

std::string TerrainGenerator::generateMapLine(int hPos)
{
    std::string result("");

    result += mapTexture::OWALL;
    if (hPos % 2 == 0) {
        for (int index = 1; index < _width - 1; index++) {
            if (index % 2 == 0)
                result += mapTexture::INWALL;
            else
                result += ' ';
        }
    } else {
        for (int index = 1; index < _width - 1; index++)
            result += ' ';
    }
    result += mapTexture::OWALL;
    return result;
}

/**
 * Private - Random Map
 */

void TerrainGenerator::cloneReverseMap()
{
    int index = 0;
    std::string tempString;
    bool reverseMap = rand() % 2 == 0 ? true : false;
    std::vector<std::string> tempMap;

    if (reverseMap)
        tempMap = _map;
    for (auto &it : _map) {
        if (index != 0 && index < _height-1) {
            if (reverseMap)
                tempString = std::string(tempMap[_height-1-index].rbegin()-1, tempMap[_height-1-index].rend()-1);
            else
                tempString = std::string(it.rbegin()-1, it.rend()-1);
            tempString.erase(0, 2);
            tempString += mapTexture::OWALL;
            it += tempString;
        } else {
            it += std::string(_width/2, mapTexture::OWALL);
        }
        index++;
    }
}

bool TerrainGenerator::blocksPath(int y, int x)
{
    if ((_map[y-1][x-1] != ' '
    && _map[y-1][x] == ' '
    && _map[y-1][x+1] != ' ')
    || (_map[y][x-1] != ' '
    && _map[y][x] == ' '
    && _map[y][x+1] != ' ')
    || (_map[y+1][x-1] != ' '
    && _map[y+1][x] == ' '
    && _map[y+1][x+1] != ' ')
    || (_map[y-1][x-1] != ' '
    && _map[y][x-1] == ' '
    && _map[y+1][x-1] != ' ')
    || (_map[y-1][x] != ' '
    && _map[y][x] == ' '
    && _map[y+1][x] != ' ')
    || (_map[y-1][x+1] != ' '
    && _map[y][x+1] == ' '
    && _map[y+1][x+1] != ' '))
        return true;
    return false;
}

void TerrainGenerator::fillHoles()
{
    for (int y = 0; y < _height-1; y++) {
        for (int x = 0; x < _width-1; x++) {
            if (_map[y][x] == ' ' && !blocksPath(y, x))
                _map[y][x] = mapTexture::INWALL;
        }
    }
}

bool TerrainGenerator::tryPlacingTile(const std::vector<std::string> &tile, int mapPos)
{
    int tileWidth = static_cast<int>(tile[0].size());
    int tileHeight = static_cast<int>(tile.size());
    bool mayPlaceIt = false;
    size_t offset = 0;

    for (; !mayPlaceIt && offset < _map.size()/2;) {
        mayPlaceIt = true;
        for (int y = 0; y < tileHeight && mayPlaceIt; y++) {
            for (int x = 0; x < tileWidth && mayPlaceIt; x++) {
                if (tile[y][x] != 'x') {
                    if (_map[mapPos+y][offset+x] != ' ')
                        mayPlaceIt = false;
                }
            }
        }
        if (!mayPlaceIt)
            offset++;
    }
    if (!mayPlaceIt && offset >= _map.size()/2)
        return false;
    for (int y = 0; y < tileHeight; y++) {
        for (int x = 0; x < tileWidth; x++) {
            if (tile[y][x] == 'o')
                _map[mapPos+y][offset+x] = tile[y][x];
        }
    }
    return true;
}

std::vector<std::string> TerrainGenerator::rotateTile(std::vector<std::string> tile) const
{
    std::vector<std::string> rotatedTile = tile;
    std::vector<std::string> tempTile(rotatedTile[0].size());

    for (size_t x = 0; x < rotatedTile[0].size(); x++)
        for (size_t y = 0; y < rotatedTile.size(); y++)
            tempTile[x].insert(0, 1, rotatedTile[y][x]);
    rotatedTile = tempTile;
    tempTile.clear();
    return rotatedTile;
}

bool TerrainGenerator::tryTetrPositions(const std::vector<std::string> &chosenTile)
{
    bool tetrPlaced = false;

    for (int tilePosition = 1; tilePosition < _height-1 && !tetrPlaced; tilePosition++)
        tetrPlaced = tryPlacingTile(chosenTile, tilePosition);
    return tetrPlaced;
}

bool TerrainGenerator::addTetrOnMap(const std::vector<std::vector<std::string>> &tiles)
{
    size_t baseId = rand() % tiles.size();
    std::vector<std::string> chosenTile;
    bool tetrPlaced = false;

    for (size_t tileId = baseId+1; tileId != baseId && !tetrPlaced; tileId++) {
        if (tileId == tiles.size()) {
            if (baseId == 0)
                break;
            else
                tileId = 0;
        }
        chosenTile = tiles[tileId];
        for (int rotate = 0; rotate < 4 && !tetrPlaced; rotate++) {
            if (rotate != 0)
                chosenTile = rotateTile(chosenTile);
            tetrPlaced = tryTetrPositions(chosenTile);
        }
    }
    return tetrPlaced;
}

size_t TerrainGenerator::lineGetWidth(int linePos)
{
    size_t index = _map[linePos].size();

    for (std::string::reverse_iterator it = _map[linePos].rbegin(); it != _map[linePos].rend(); it++) {
        if (index != _map[linePos].size() && *it != ' ')
            return index;
        index--;
    }
    return index;
}

bool TerrainGenerator::isMapFull()
{
    size_t maxSize = _width/2;
    int counter = 0;
    int index = 0;

    for (auto it = _map.begin(); it != _map.end(); it++) {
        if (index > 0 && index < _height-1 && lineGetWidth(static_cast<int>(it-_map.begin())) >= maxSize)
            counter++;
        index++;
    }
    if (counter > 5)
        return true;
    return false;
}

void TerrainGenerator::trimMap()
{
    for (auto &it : _map)
        if (it.size() > static_cast<size_t>(_width/2+1))
            it = it.substr(0, _width/2+1);
}
