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
#include <mutex>
#include <memory>
#include "Asset.hpp"

class AssetManager {
private:
            struct LoadStatus
            {
                float percentage;
                bool isReady;
                std::string currLoading;
                        
            };

    /**
     * @brief _mutex
     * 
     */
    std::mutex _mutex;

    /**
     * @brief vector of all assets
     * 
     */
    std::vector<std::unique_ptr<Asset>> _assets;

    /**
     * @brief _loadStatus
     * 
     */
    LoadStatus _loadStatus;

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
     * @brief Copy a new AssetManager object
     * 
     */
    AssetManager(const AssetManager&) = delete;
    /**
     * @brief Assign a new AssetManager object
     * 
     * @return AssetManager& assigned AssetManager
     */
    AssetManager& operator=(const AssetManager&) = delete;

    /**
     * @brief Load assets of the 
     * 
     * @param objects 
     */
    void loadAssets(std::list<std::unique_ptr<ECS::Entity>> &objects);

    /**
     * @brief Remove all unnecessary assets 
     * 
     * @param objects 
     */
    void removeAllUnnecessaryAssets(std::vector<std::string> &objects);

    /**
     * @brief Get the Asset From Name object
     * 
     * @param name
     * @return Asset& 
     */
    Asset &getAssetFromName(std::string &name) const;

    /**
     * @brief Find the files corresponding to the name given
     * 
     * @param name
     * @return std::vector<Asset>
     */
    std::vector<Asset> findFilesOfName(const std::string &name);

    /**
     * @brief 
     * 
     * @param name
     */
    void deleteAssetFromName(const std::string &name);

    /**
     * @brief Get the Assets object
     * 
     * @return const std::vector<Asset>&
     */
    const std::vector<std::unique_ptr<Asset>> &getAssets() const;

    /**
     * @brief Get the loadStatus
     * 
     * @return const LoadStatus&
     */
    const LoadStatus &getLoadStatus() const;
    
};

#endif /* !ASSETMANAGER_HPP_ */
