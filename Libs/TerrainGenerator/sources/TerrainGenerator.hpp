/*
** EPITECH PROJECT, 2021
** temp
** File description:
** TerrainGenerator
*/

#ifndef TERRAINGENERATOR_HPP_
#define TERRAINGENERATOR_HPP_

#include <string>
#include <vector>
#include "Vector2.hpp"

class TerrainGenerator {
    public:
        /**
         * @enum Textures displayed on map
         * 
         */
        enum class mapTexture {
            OWALL = 'X', // Outer wall character
            INWALL = 'o', // Inner wall character
            WEAKBOX = '1', // Weak box character
            MEDIUMBOX = '2', // Medium box character
            STRONGBOX = '3', // Strong box character
            PLAYER = 'P' // Player character
        };
        /**
         * @enum Map types
         * 
         */
        enum class MapType {
            Default, // Generate a basic or random map with the respective ratio 1/3:2/3
            Basic, // Generate a basic map
            Random // Generate a random map
        };
        /**
         * @brief Construct a new Terrain Generator:: Terrain Generator object
         * 
         * @param playersNbr 
         * @param mapType 
         * @param boxPercentage 
         */
        TerrainGenerator(int playersNbr, const MapType mapType = MapType::Default, int boxPercentage = 80);
        /**
         * @brief Construct a new Terrain Generator object
         * 
         * @param playersNbr Number of players (From 1 to 8)
         * @param boxPercentage Percentage of box spawning (80 by default)
         */
        TerrainGenerator(int playersNbr, int width, int height, const MapType mapType = MapType::Default, int boxPercentage = 80);
        /**
         * @brief Destroy the Terrain Generator object
         * 
         */
        ~TerrainGenerator() = default;
        /**
         * @brief Construct a new Terrain Generator object
         * 
         * @param other 
         */
        TerrainGenerator(const TerrainGenerator& other) = default;
        /**
         * @brief Assignment operator
         * 
         * @param other 
         * @return TerrainGenerator& 
         */
        TerrainGenerator& operator=(const TerrainGenerator& other) = default;

        /**
         * @brief Get the Map object
         * 
         * @return std::vector<std::string> 
         */
        const std::vector<std::string>& getMap() const;
        /**
         * @brief Display the map on standard output
         * 
         */
        void displayMap();
        /**
         * @brief Generate bomberman's basic map
         * 
         */
        void generateBaseMap(int seed);
        /**
         * @brief Generate procedurally generated map
         * 
         * @param seed The seed randomizer
         */
        void generateRandomMap(int seed);
        /**
         * @brief Clear the map objects and only keep outer walls
         * 
         */
        void clearMap();
        /**
         * @brief Add a new wall on the map
         * 
         * @param y Height position
         * @param x Width position
         */
        void addTileOnMap(int y, int x);
        /**
         * @brief Generate the _map object into an "map.xml" file
         * 
         */
        void generateXMLFile();
        /**
         * @brief Set the Players Number object
         * Resets the map according to players number
         * 
         * @param newSize The new player numbers
         */
        void setPlayersNumber(int newSize);

        /**
         * @brief Set the Map Size object
         * 
         * @param mapSize 
         */
        void setMapSize(RayLib::Vector2<int> mapSize);

        /**
         * @brief If a map has been generated
         * 
         * @return bool
         */
        bool isGenerated();

        /**
         * @brief Randomly generate boxes for Random and Basic maps
         * 
         */
        void generateBoxes();
        /**
         * @brief Place players on map based on their number
         * Specific to Random maps
         * 
         */
        void placePlayers();

        void SetMap(std::vector<std::string> map);

        void SetIsGenerated(bool value);

    protected:
        /**
         * @brief Generate a line based on the actual position
         * Specific to Basic maps
         * 
         * @param hPos Map position to generate
         * @return std::string The generated line
         */
        std::string generateMapLine(int hPos);
        /**
         * @brief Generate a random level for a box
         * 
         * @return char Box level '1', '2' or '3'
         */
        char generateBoxLevel();
        /**
         * @brief Clone the generated map mirror on the other face
         * Specific to Random maps
         * 
         */
        void cloneReverseMap();
        /**
         * @brief Check if a wall on the current position blocks the map
         * Specific to Random maps
         * 
         * @param y Height posiiton
         * @param x Width position
         * @return true A wall on this position wouldn't block the path
         * @return false A wall on this position would block the path
         */
        bool blocksPath(int y, int x);
        /**
         * @brief Fill the map holes so that paths are 1 tile wide
         * Specific to Random maps
         * Commented function for now
         * 
         */
        void fillHoles();
        /**
         * @brief Try placing a tile on a map height position
         * Specific to Random maps
         * 
         * @param tile The tile to place on the map
         * @param mapPos The height to test on
         * @return true The tile has been placed
         * @return false The tile has not been placed
         */
        bool tryPlacingTile(const std::vector<std::string> &tile, int mapPos);
        /**
         * @brief Rotate a tile one tile clockwise
         * Specific to Random maps
         * 
         * @param tile The tile to rotate
         * @return std::vector<std::string> The rotated tile
         */
        std::vector<std::string> rotateTile(std::vector<std::string> tile) const;
        /**
         * @brief Try placing a tile on all map heights
         * Specific to Random maps
         * 
         * @param chosenTile The tile to place on the map
         * @return true The tile has been placed
         * @return false The tile has not been placed
         */
        bool tryTetrPositions(const std::vector<std::string> &chosenTile);
        /**
         * @brief Try placing a new tile on the map
         * Specific to Random maps
         * 
         * @param tiles The available tiles
         * @return true The tile has been placed
         * @return false No more tiles can be placed
         */
        bool addTetrOnMap(const std::vector<std::vector<std::string>> &tiles);
        /**
         * @brief Get the size of a map's line regardless of the outwalls
         * Specific to Random maps
         * 
         * @param linePos Position to check on
         * @return size_t The size of the line
         */
        size_t lineGetWidth(int linePos);
        /**
         * @brief Check if the map can accept more tiles
         * Specific to Random maps
         * 
         * @return true The map can accept more tiles
         * @return false The map cannot accept more tiles
         */
        bool isMapFull();
        /**
         * @brief Randomly generates either a Basic map or a Random one 
         * 
         */
        void generateMap();
        /**
         * @brief Cut the map in half
         * 
         */
        void trimMap();
        /**
         * @brief Add holes between player places to place safe bombs
         * 
         */
        void makeSpaceForPlayers();

        /**
         * @brief Number of players rounded to next pair
         * 
         */
        int _playersNbr;
        /**
         * @brief Percentage of box apparition on map
         * 
         */
        int _boxPercentage;
        /**
         * @brief Map height
         * 
         */
        int _height;
        /**
         * @brief Map width
         * 
         */
        int _width;
        /**
         * @brief Current map type
         * 
         */
        MapType _mapType;
        /**
         * @brief The map
         * 
         */
        std::vector<std::string> _map;

        /**
         * @brief If a map has been generated
         * 
         */
        bool _isGenerated;
};

#endif /* !TERRAINGENERATOR_HPP_ */
