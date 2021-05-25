/*
** EPITECH PROJECT, 2021
** temp
** File description:
** TerrainGenerator
*/

#ifndef MAPPER_HPP_
#define MAPPER_HPP_

#include <string>
#include <vector>

class TerrainGenerator {
    public:
        typedef struct s_vector2 {
            int x;
            int y;
        }vector2_t;
        enum mapTexture {
            OWALL = 'O',
            INWALL = 'o'
        };
        TerrainGenerator(int playersNbr, int boxPercentage = 80);
        ~TerrainGenerator();

        std::vector<std::string> getMap() const;
        void displayMap();
        void generateBaseMap();
        void generateRandomMap();
        void clearMap();
        void addTileOnMap(vector2_t tilePosition);
    protected:
        std::string generateMapLine(int hPos);
        void generateBoxes();
        void cloneReverseMap();
        std::string generateRandomMapLine(std::string previousString, int hPos);
        bool tryPlacingTile(const std::vector<std::string> &tile, int mapPos);
        std::vector<std::string> rotateTile(std::vector<std::string> tile) const;
        void removeVoid();
        bool tryTetrPositions(const std::vector<std::string> &chosenTile);
        bool addTetrOnMap(const std::vector<std::vector<std::string>> &tiles);
        size_t lineGetWidth(int linePos);
        bool isMapFull();
        void placePlayers();
        void generateMap();
        void trimMap();

        int _playersNbr;
        int _boxPercentage;
        int _height;
        int _width;
        std::vector<std::string> _map;
};

#endif /* !MAPPER_HPP_ */
