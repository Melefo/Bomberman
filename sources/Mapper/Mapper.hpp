/*
** EPITECH PROJECT, 2021
** temp
** File description:
** Mapper
*/

#ifndef MAPPER_HPP_
#define MAPPER_HPP_

#include <cstdint>
#include <string>
#include <vector>

class Mapper {
    public:
        Mapper(uint8_t playersNbr);
        ~Mapper();

        std::vector<std::string> &getMap() const;
    private:
        void generateMap();

        uint8_t _playersNbr;
        uint8_t _height;
        uint8_t _width;
        std::vector<std::string> _map;
};

#endif /* !MAPPER_HPP_ */
