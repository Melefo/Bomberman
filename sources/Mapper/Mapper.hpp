/*
** EPITECH PROJECT, 2021
** temp
** File description:
** Mapper
*/

#ifndef MAPPER_HPP_
#define MAPPER_HPP_

#include <string>
#include <vector>

class Mapper {
    public:
        Mapper(int playersNbr, int boxPercentage = 80);
        ~Mapper();

        std::vector<std::string> getMap() const;
    protected:
        std::string generateMapLine(int hPos);
        void generateBaseMap();
        void generateBoxes();
        void generateMap();

        int _playersNbr;
        int _boxPercentage;
        int _height;
        int _width;
        std::vector<std::string> _map;
};

#endif /* !MAPPER_HPP_ */
