/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** testMapper
*/

#ifndef TESTMAPPER_HPP_
#define TESTMAPPER_HPP_

#include "Mapper.hpp"

class TestMapper : public Mapper {
    public:
        TestMapper(int playersNbr) : Mapper(playersNbr, 70) {};
        ~TestMapper() = default;

        std::string generateMapLine(int hPos) {
            return Mapper::generateMapLine(hPos);
        };
        void removeBoxes() {
            for (auto &it : _map)
                std::replace(it.begin(), it.end(), 'x', ' ');
        };
};

#endif /* !TESTMAPPER_HPP_ */
