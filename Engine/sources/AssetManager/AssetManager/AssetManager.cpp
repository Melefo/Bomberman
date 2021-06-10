/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** AssetManager
*/

#include <filesystem>
#include <list>
#include "AssetManager.hpp"
#include "Entity.hpp"

AssetManager::AssetManager() :
    _mutex(), _assets(), _loadStatus({0.0, false, ""})
{
    
}

AssetManager::~AssetManager()
{
    
}

void AssetManager::loadAssets(std::list<std::unique_ptr<ECS::Entity>> &objects)
{
    bool isAlreadyLoaded = false;

    _mutex.lock();
    _loadStatus = {0.0, false, "Unloading unnecessary assets..."};
    _mutex.unlock();
    removeAllUnnecessaryAssets(objects);
    for (auto &object : objects) {
        _mutex.lock();
        _loadStatus.currLoading = "Loading the " + object->GetTag + "\'s asset...";
        _mutex.unlock();
        isAlreadyLoaded = false;
        for (auto &asset : _assets) {
            if (asset->getName() == object->GetTag()) {
                isAlreadyLoaded = true;
                break;
            }
        }
        if (isAlreadyLoaded == false) {
            Asset newAsset(object);
            _assets.push_back(std::make_unique<Asset>(newAsset));
        }
        _mutex.lock();
        _loadStatus.percentage = (_assets.size() * 100) / objects.size();
        _mutex.unlock();
    }
    _mutex.lock();
    _loadStatus = {100.0, true, "Loading done!"};
    _mutex.unlock();
}

Asset &AssetManager::getAssetFromName(std::string &name) const
{
    for (auto &asset : _assets) {
        if (asset->getName() == name)
            return (*asset);
    }
    throw("");//TODO
}

void AssetManager::removeAllUnnecessaryAssets(std::list<std::unique_ptr<ECS::Entity>> &objects)
{
    bool isNeeded = false;

    for (auto &asset : _assets) {
        isNeeded = false;
        for (auto &object : objects) {
            if (asset->getName() == object->GetTag()) {
                isNeeded = true;
                break;
            }
        }
        if (isNeeded == false)
            deleteAssetFromName(asset->getName());
    }
}

void AssetManager::deleteAssetFromName(const std::string &name)
{
    for (auto &asset : _assets) {
        if (asset->getName() == name) {
            //_assets.erase(std::remove(asset));
            return;
        }
    }
}

const std::vector<std::unique_ptr<Asset>> &AssetManager::getAssets() const
{
    return (_assets);
}

const AssetManager::LoadStatus &AssetManager::getLoadStatus() const
{
    return (_loadStatus);
}
