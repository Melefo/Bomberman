/*
** EPITECH PROJECT, 2021
** temp
** File description:
** Mapper
*/

#include "Mapper.hpp"
#include <map>
#include <cstdlib>

Mapper::Mapper(int playersNbr, int boxPercentage = 70)
    : _playersNbr(playersNbr % 2 == 0 ? playersNbr : playersNbr++), _boxPercentage(boxPercentage),
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

Mapper::~Mapper()
{
}

std::string Mapper::generateMapLine(int hPos)
{
    std::string result;

    result += 'W';
    if (hPos % 2 == 0) {
        for (int index = 1; index < _width - 1; index++)
            result += ' ';
    } else {
        for (int index = 1; index < _width - 1; index++) {
            if (index % 2 == 0)
                result += 'w';
            else
                result += ' ';
        }
    }
    result += 'W';
    return result;
}

void Mapper::generateBaseMap()
{
    int index = 0;

    for (std::vector<std::string>::iterator it = _map.begin(); it != _map.end(); it++, index++) {
        if (index == 0 || index == _height - 1)
            *it = std::string(_width, 'W');
        else
            *it = generateMapLine(index);
    }
}

void Mapper::generateBoxes()
{
    for (std::vector<std::string>::iterator it = _map.begin()+1; it != _map.end()-1; it++) {
        for (std::size_t index = 1; index != it->length()-1; index++) {
            if ((*it)[index] == ' ') {
                (*it)[index] = rand() % _boxPercentage+1 < _boxPercentage ? 'x' : ' ';
            }
        }
    }
}

void Mapper::generateMap()
{
    generateBaseMap();
    generateBoxes();
}

/**
 * Getters
 */

std::vector<std::string> Mapper::getMap() const
{
    return _map;
}
