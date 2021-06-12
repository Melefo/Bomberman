/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** AssetManager
*/

#include <filesystem>
#include <list>
#include <thread>
#include <algorithm>
#include "Entity.hpp"
#include "AssetManager.hpp"
#include "Entity.hpp"
#include "Exceptions.hpp"
#include "Renderer.hpp"

AssetManager::AssetManager() :
    _mutex(), _assets(), _loadStatus({0.0, false, ""})
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::loadAssetsThreadFunc(std::vector<std::string> objects)
{
    bool isAlreadyLoaded = false;

    //_mutex.lock();
    _loadStatus = {0.0, false, "Unloading unnecessary assets..."};
    //_mutex.unlock();
    removeAllUnnecessaryAssets(objects);
    for (auto &object : objects) {
        //_mutex.lock();
        _loadStatus.currLoading = "Loading the " + object + "\'s asset...";
        //_mutex.unlock();
        isAlreadyLoaded = false;
        for (auto &asset : _assets) {
            if (asset->getName() == object) {
                isAlreadyLoaded = true;
                break;
            }
        }
        if (isAlreadyLoaded == false) {
            try {
                //Asset newAsset(object);

                //_mutex.lock();
                std::cout << "Making object with name" << object << std::endl;
                _assets.push_back(std::make_unique<Asset>(object));
                //_mutex.unlock();
            } catch (const ECS::Exception::AssetException &error) {
                std::cerr << error.what() << std::endl;
            }
        }
        //_mutex.lock();
        _loadStatus.percentage = (_assets.size() * 100) / objects.size();
        //_mutex.unlock();
    }
    //_mutex.lock();
    _loadStatus = {100.0, true, "Loading done!"};
    //_mutex.unlock();
}

void AssetManager::loadAssets(const std::list<std::unique_ptr<ECS::Entity>> &objects)
{
    //std::thread thread(&AssetManager::loadAssetsThreadFunc, this, getNamesOfObjects(objects));
//
    //thread.detach();
    loadAssetsThreadFunc(getNamesOfObjects(objects));
}

void AssetManager::addAssetOfName(const std::string &name)
{
    for (auto &asset : _assets) {
        if (asset->getName() == name)
            return;
    }
    try {
        _assets.push_back(std::make_unique<Asset>(name));
    } catch (const ECS::Exception::AssetException &error) {
        std::cerr << error.what() << std::endl;
    }
}

Asset &AssetManager::getAssetFromName(const std::string &name)
{
    for (auto &asset : _assets) {
        if (asset->getName() == name)
            return (*asset);
    }
    addAssetOfName(name);
    for (auto &asset : _assets) {
        if (asset->getName() == name)
            return (*asset);
    }
    throw ECS::Exception::AssetManagerException("Cannot find an Asset with the name " + name + ".");
}

std::vector<std::string> AssetManager::getNamesOfObjects(const std::list<std::unique_ptr<ECS::Entity>> &objects)
{
    std::vector<std::string> names;

    for (auto &object : objects) {
        if (object.get()->HasComponent<Component::Renderer>()) {
            Component::Renderer& renderer = object->GetComponent<Component::Renderer>();
            //if (std::find (names.begin(), names.end(), object->GetTag()) == names.end())
            //    names.push_back(object->GetTag());
            if (std::find (names.begin(), names.end(), renderer.getName()) == names.end())
                names.push_back(renderer.getName());
        }
    }
    return (names);
}

void AssetManager::removeAllUnnecessaryAssets(std::vector<std::string> &objects)
{
    bool isNeeded = false;

    for (auto &asset : _assets) {
        isNeeded = false;
        for (auto &object : objects) {
            if (asset->getName() == object) {
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
    std::vector<std::unique_ptr<Asset>>::iterator it = _assets.begin();

    for (; it != _assets.end(); it++) {
        if ((*it)->getName() == name) {
            //_mutex.lock();
            //_assets.erase(it);              //Si ça marche pas c'est ici
            //_mutex.unlock();
        }
    }
}

std::unique_ptr<AssetManager> AssetManager::_assetManager = nullptr;

std::unique_ptr<AssetManager>& AssetManager::GetInstance()
{
    if (_assetManager == nullptr)
        _assetManager = std::make_unique<AssetManager>();
    return (_assetManager);
}

const std::vector<std::unique_ptr<Asset>> &AssetManager::getAssets() const
{
    return (_assets);
}

const AssetManager::LoadStatus &AssetManager::getLoadStatus() const
{
    return (_loadStatus);
}

const std::string AssetManager::getNextScene() const
{
    return this->_nextScene;
}

void AssetManager::setNextScene(std::string &nextScene)
{
    this->_nextScene = nextScene;
}

void AssetManager::lock()
{
    _mutex.lock();
}

void AssetManager::unlock()
{
    _mutex.unlock();
}
