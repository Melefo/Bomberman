/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** Asset
*/

#include <filesystem>
#include "Asset.hpp"

Asset::Asset(std::string name) :
    _name(name)
{
    std::string file;

    for (auto &element : std::filesystem::recursive_directory_iterator("./assets/")) {
        file = element.path();
        if (file.find(name)) {
            if (file.find("model") != std::string::npos) {
                _model = std::make_unique<RayLib::Model>(file);
            } else if (file.find("anim") != std::string::npos) {
                _animations.emplace(getFileNameWithoutExt(file), file);
            } else if (file.find("texture") != std::string::npos) {
                _texture = std::make_unique<RayLib::Texture>(file);
            }
        }
    }
}

Asset::~Asset()
{
}

Asset& Asset::operator=(Asset& asset)
{
    this->_name = asset.getName();
    this->_model.reset(asset.getModel().release());
    this->_texture.reset(asset.getTexture().release());
    this->_animations.clear();
    for (auto &animation : asset.getAnimations())
        this->_animations.emplace(animation.first, animation.second);
    return (*this);
}

std::string Asset::getFileNameWithoutExt(const std::string &filePath)
{
    size_t lastFolder = filePath.find_last_of("/");
    size_t extDot;

    if (lastFolder == std::string::npos)
        filePath.find_last_of(".");
    else
        filePath.substr(lastFolder, std::string::npos).find_last_of(".");
    if (extDot == std::string::npos && lastFolder == std::string::npos)
        return filePath;
    else if (extDot == std::string::npos)
        return filePath.substr(lastFolder, std::string::npos);
    else if (lastFolder == std::string::npos)
        return filePath.substr(0, extDot);
    return filePath.substr(lastFolder, extDot - lastFolder);
}

std::unique_ptr<RayLib::Texture> &Asset::getTexture()
{
    return (_texture);
}

std::unique_ptr<RayLib::Model> &Asset::getModel()
{
    return (_model);
}

std::map<std::string, ModelAnimation> &Asset::getAnimations()
{
    return (_animations);
}
