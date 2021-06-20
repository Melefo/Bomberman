/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** ModelShader
*/

#include "ModelShader.hpp"
#include "AssetCache.hpp"
#include "Shader.hpp"

namespace Component {
    ModelShader::ModelShader(const std::string shaderPath)
    {
        AssetCache::GetAsset<RayLib::Shader>(shaderPath);
    }

    std::ostream &ModelShader::operator<<(std::ostream &os)
    {
        return (os);
    }

    std::istream &ModelShader::operator>>(std::istream &is)
    {
        return (is);
    }

    boost::property_tree::ptree& ModelShader::operator<<(boost::property_tree::ptree &ptree)
    {
        return (ptree);
    }
}
