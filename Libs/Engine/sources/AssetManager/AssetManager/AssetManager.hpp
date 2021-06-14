/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** AssetManager
*/

#ifndef ASSETMANAGER_HPP_
#define ASSETMANAGER_HPP_

#include <vector>
#include <mutex>
#include <memory>
#include "Asset.hpp"
#include "Entity.hpp"

class AssetManager {
private:
    /**
     * @brief Coordinator singleton
     * 
     */
    static std::unique_ptr<AssetManager> _assetManager;

    /**
     * @brief struct LoadStatus
     * 
     */
    struct LoadStatus
    {
        float percentage;
        bool isReady;
        std::string currLoading;
    };

    /**
     * @brief _nextScene
     * 
     */
    std::string _nextScene;

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

    /**
     * @brief Load assets of the 
     * 
     * @param objects 
     */
    void loadAssetsThreadFunc(std::map<std::string, uint32_t> objects);

    /**
     * @brief Returns the names of the objects in the entity list
     * 
     * @param objects 
     */
    std::map<std::string, uint32_t> getNamesOfObjects(const std::list<std::unique_ptr<ECS::Entity>> &objects);

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
    ~AssetManager() = default;

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
    void loadAssets(const std::list<std::unique_ptr<ECS::Entity>> &objects);

    /**
     * @brief Add the asset given
     * 
     * @param name 
     */
    void addAssetOfName(const std::string &name);

    /**
     * @brief Remove all unnecessary assets 
     * 
     * @param objects 
     */
    void removeAllUnnecessaryAssets(std::map<std::string, uint32_t> &objects);

    /**
     * @brief Get the Asset From Name object
     * 
     * @param name
     * @return Asset& 
     */
    Asset &getAssetFromName(const std::string &name);

    /**
     * @brief Get the Asset with name and ID
     * 
     * @param name 
     * @param id 
     * @return Asset& 
     */
    Asset &getAssetFromName(const std::string &name, uint32_t id);


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

    /**
     * @brief Get the Next Scene object
     * 
     * @return const std::string 
     */
    const std::string getNextScene() const;

    /**
     * @brief Set the Next Scene object
     * 
     * @param nextScene 
     */
    void setNextScene(std::string &nextScene);

    /**
     * @brief Lock the mutex
     * 
     */
    void lock();

    /**
     * @brief Unlock the mutex
     * 
     */
    void unlock();

    /**
    * @brief Get a unique_ptr to the assetManager Singleton
    * 
    * @return std::unique_ptr<AssetManager>& 
    */
    static std::unique_ptr<AssetManager>& GetInstance();
};

#endif /* !ASSETMANAGER_HPP_ */
