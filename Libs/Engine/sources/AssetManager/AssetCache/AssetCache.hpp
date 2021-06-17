/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AssetCache
*/

#ifndef ASSETCACHE_HPP_
#define ASSETCACHE_HPP_

#include "IAsset.hpp"
#include "EngineExceptions.hpp"
#include <map>
#include <memory>

/**
 * @brief Manages game assets
 * Makes sure every asset is loaded once
 * 
 */
class AssetCache {
    public:
        /**
         * @brief Construct a new Asset Cache object
         * 
         */
        AssetCache() = default;
        /**
         * @brief Destroy the Asset Cache object
         * 
         */
        ~AssetCache() = default;

        /**
         * @brief Get the Asset object
         * When getting Shaders, extention must not be provided (.vs/.fs)
         * 
         * @tparam T Mesh/Texture/Shader
         * @param path Path to the asset
         * @return T& 
         */
        template<typename T>
        static T& GetAsset(const std::string& path)
        {
            const auto &it = _assets.find(path);

            if (it == _assets.end()) {
                _assets[path] = std::make_unique<T>(path);
                return (dynamic_cast<T&>(*_assets[path]));
            }
            return (dynamic_cast<T&>(*it->second));
        }

        /* ? Targs ... ?
        template<typename T>
        T& CreateAsset(const std::string& path)
        {
            T& asset = T(path);
        }*/

    protected:
    private:
        /**
         * @brief Loaded assets
         * String for the path, IAsset for the asset
         * 
         */
        static std::map<std::string, std::unique_ptr<RayLib::IAsset>> _assets;
};

#endif /* !ASSETCACHE_HPP_ */
