/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** Asset
*/

#ifndef ASSET_HPP_
#define ASSET_HPP_

#include "Model.hpp"
#include "Texture.hpp"
#include "raylib.h"

class Asset {
    private:

        std::map<std::string, ModelAnimation> 
        /**
         * @brief 
         * 
         */
        RayLib::Model _model;
        
        /**
         * @brief 
         * 
         */
        RayLib::Texture _texture;

        /**
         * @brief 
         * 
         */
        std::string _name;

    public:
        /**
         * @brief Construct a new Asset object
         * 
         */
        Asset();

        /**
         * @brief Destroy the Asset object
         * 
         */
        ~Asset();

        /**
         * @brief Get the Name object
         * 
         * @return const std::string& 
         */
        const std::string &getName() const;

        /**
         * @brief Get the Model object
         * 
         * @return const RayLib::Model& 
         */
        const RayLib::Model &getModel() const;

        /**
         * @brief Get the Texture object
         * 
         * @return const RayLib::Texture& 
         */
        const RayLib::Texture &getTexture() const;
};

#endif /* !ASSET_HPP_ */
