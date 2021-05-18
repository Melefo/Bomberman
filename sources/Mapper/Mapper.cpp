/*
** EPITECH PROJECT, 2021
** temp
** File description:
** Mapper
*/

#include "Mapper.hpp"
#include <map>

Mapper::Mapper(uint8_t playersNbr) : _playersNbr(playersNbr % 2 == 0 ? playersNbr : playersNbr++), _height(13)
{
    std::map<int, int> mapSizes = {
        {2, 13},
        {4, 15},
        {6, 17},
        {8, 19}
    };

    _width = mapSizes[_playersNbr];
    generateMap();
}

Mapper::~Mapper()
{
}

void Mapper::generateMap()
{
}

/**
 * Getters
 */

std::vector<std::string> &Mapper::getMap() const
{
}
