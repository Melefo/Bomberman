/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** AssetManager
*/

#ifndef ASSETMANAGER_HPP_
#define ASSETMANAGER_HPP_

#include <map>
#include <vector>
#include "Asset.hpp"

class AssetManager {
    private:
        std::vector<Asset> _assets;
    public:
        /**
         * @brief Construct a new Asset Manager object
         * 
         */
        AssetManager();
        /**
         * @brief Destroy the Asset Manager object
         * 
         */
        ~AssetManager();

        /**
         * @brief Get the Asset From Name object
         * 
         * @param name 
         * @return Asset& 
         */
        Asset &getAssetFromName(std::string name) const;

        /**
         * @brief 
         * 
         * @param name 
         * @return true 
         * @return false 
         */
        bool deleteAssetFromName(std::string name);

        /**
         * @brief Get the Assets object
         * 
         * @return const std::vector<Asset> 
         */
        const std::vector<Asset> getAssets() const;
};

#endif /* !ASSETMANAGER_HPP_ */
