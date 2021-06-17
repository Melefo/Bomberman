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
#include "Sound.hpp"

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
        std::unique_ptr<RayLib::Mesh> _mesh;

        /**
         * @brief 
         * 
         */
        std::unique_ptr<RayLib::Texture> _texture;

        /**
         * @brief 
         * 
         */
        std::map<std::string, RayLib::Sound> _sounds;

        /**
         * @brief 
         * 
         */
        std::string _name;

        /**
         * @brief entityID
         * 
         */
        uint32_t _entityID;

    public:
        /**
         * @brief Construct a new Asset object
         * 
         */
        Asset(std::string name, uint32_t id=-1);

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
        static std::string getFileNameWithoutExt(const std::string &filePath);

        /**
         * @brief Get the Name object
         * 
         * @return const std::string& 
         */
        std::string getAnimationName(const std::string &filePath);

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
        RayLib::Model &getModel();

        /**
         * @brief Get the Texture object
         * 
         * @return std::unique_ptr<RayLib::Texture>& 
         */
        RayLib::Texture &getTexture();

        /**
         * @brief Get the Animations object
         * 
         * @return const ModelAnimation& 
         */
        std::map<std::string, RayLib::ModelAnimation> &getAnimations();

        /**
         * @brief 
         * 
         */
        std::map<std::string, RayLib::Sound>& getSounds();

        uint32_t getID(void);

};

#endif /* !ASSET_HPP_ */
