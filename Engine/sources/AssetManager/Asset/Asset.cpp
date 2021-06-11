/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** Asset
*/

#include <filesystem>
#include "Exceptions.hpp"
#include "Asset.hpp"

Asset::Asset(std::string name)
    : _name(name)
{
    std::string file;

    for (auto &element : std::filesystem::recursive_directory_iterator("../assets/")) {
        file = element.path();
        if (element.symlink_status().type() == std::filesystem::file_type::directory)
            continue;
        if (file.find(name) != std::string::npos) {
            if (file.find("model") != std::string::npos) {
                _model = std::make_unique<RayLib::Model>(file);
            } else if (file.find("anim") != std::string::npos) {
                _animations.emplace(getAnimationName(file), file);
            } else if (file.find("texture") != std::string::npos) {
                _texture = std::make_unique<RayLib::Texture>(file);
            }
        }
    }
    if (_animations.size() == 0 && _model == nullptr && _texture == nullptr)
        throw ECS::Exception::AssetException("Cannot find any asset for \"" + name + "\".");
}

Asset::Asset(Asset &other)
    : _animations(), _model(std::make_unique<RayLib::Model>(other.getModel().GetFileName())), _texture(std::make_unique<RayLib::Texture>(other.getTexture().GetFileName())), _name(other.getName())
{
    for (auto &animation : other.getAnimations())
        this->_animations.emplace(animation.first, animation.second);
}

Asset::~Asset()
{
}

Asset& Asset::operator=(Asset& other)
{
    this->_name = other.getName();
    this->_model = std::make_unique<RayLib::Model>(other.getModel().GetFileName());
    this->_texture = std::make_unique<RayLib::Texture>(other.getTexture().GetFileName());
    this->_animations.clear();
    for (auto &animation : other.getAnimations())
        this->_animations.emplace(animation.first, animation.second);
    return (*this);
}

std::string Asset::getAnimationName(const std::string &filePath)
{
    std::string name = getFileNameWithoutExt(filePath);
    std::size_t separatorIdx = name.find_last_of("_");

    if (separatorIdx == std::string::npos)
        return ("unknown");
    return (name.substr(separatorIdx + 1, std::string::npos));
}

std::string Asset::getFileNameWithoutExt(const std::string &filePath)
{
    size_t lastFolder = filePath.find_last_of("/");
    size_t extDot = filePath.find_last_of(".");

    if (extDot == std::string::npos && lastFolder == std::string::npos)
        return filePath;
    else if (extDot == std::string::npos)
        return filePath.substr(lastFolder + 1, std::string::npos);
    else if (lastFolder == std::string::npos)
        return filePath.substr(0, extDot - 1);
    return filePath.substr(lastFolder + 1, extDot - lastFolder - 1);
}

const std::string &Asset::getName() const
{
    return (_name);
}

const RayLib::Texture &Asset::getTexture() const
{
    return (*_texture);
}

RayLib::Model &Asset::getModel()
{
    return (*_model);
}

std::map<std::string, RayLib::ModelAnimation> &Asset::getAnimations()
{
    return (_animations);
}
