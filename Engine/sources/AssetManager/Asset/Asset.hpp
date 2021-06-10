/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** Asset
*/

#ifndef ASSET_HPP_
#define ASSET_HPP_

#include <map>
#include "Model.hpp"
#include "Texture.hpp"
#include "ModelAnimation.hpp"
#include <memory>

class Asset {
    private:

        std::map<std::string, RayLib::ModelAnimation> _animations;
        /**
         * @brief 
         * 
         */
        std::unique_ptr<RayLib::Model> _model;

        /**
         * @brief 
         * 
         */
        std::unique_ptr<RayLib::Texture> _texture;

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
        Asset(std::string name);

        /**
         * @brief Destroy the Asset object
         * 
         */
        ~Asset();

        /**
         * @brief Construct a new Asset object
         * 
         */
        Asset(Asset&);

        /**
         * @brief Assign a new Asset object
         * 
         * @return Asset& assigned Asset
         */
        Asset& operator=(Asset&);

        /**
         * @brief Get the Name object
         * 
         * @return const std::string& 
         */
        std::string getFileNameWithoutExt(const std::string &filePath);

        /**
         * @brief Get the Name object
         * 
         * @return const std::string& 
         */
        const std::string &getName() const;

        /**
         * @brief Get the Model object
         * 
         * @return std::unique_ptr<RayLib::Model>& 
         */
        const std::unique_ptr<RayLib::Model> &getModel() const;

        /**
         * @brief Get the Texture object
         * 
         * @return std::unique_ptr<RayLib::Texture>& 
         */
        const std::unique_ptr<RayLib::Texture> &getTexture() const;

        /**
         * @brief Get the Animations object
         * 
         * @return const ModelAnimation& 
         */
        std::map<std::string, RayLib::ModelAnimation> &getAnimations();
};

#endif /* !ASSET_HPP_ */
