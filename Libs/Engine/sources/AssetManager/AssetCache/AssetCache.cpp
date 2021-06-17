/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AssetCache
*/

#include "AssetCache.hpp"

std::map<std::string, std::unique_ptr<RayLib::IAsset>> AssetCache::_assets;
