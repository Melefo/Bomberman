/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Drawable3D
*/

#include "Drawable3D.hpp"
#include "AssetCache.hpp"

namespace Component
{
    Drawable3D::Drawable3D(RayLib::Mesh& mesh) : 
    _model(std::make_shared<RayLib::Model>(mesh)), _texture(nullptr), _shader(nullptr)
    {
    }

    Drawable3D::Drawable3D(const std::string& modelPath) :
    _model(AssetCache::GetAsset<RayLib::Model>(modelPath)), _texture(nullptr), _shader(nullptr)
    {
    }

    Drawable3D::Drawable3D(const std::string& modelPath, const std::string& texturePath) :
    _model(AssetCache::GetAsset<RayLib::Model>(modelPath)),
    _texture(AssetCache::GetAsset<RayLib::Texture>(texturePath)), _shader(nullptr)
    {
        SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, *_texture);
    }

    Drawable3D::Drawable3D(const std::string& modelPath, const std::string& texturePath, const std::string& shaderPath) :
    _model(AssetCache::GetAsset<RayLib::Model>(modelPath)),
    _texture(AssetCache::GetAsset<RayLib::Texture>(texturePath)),
    _shader(AssetCache::GetAsset<RayLib::Shader>(shaderPath))
    {
        SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, *_texture);
        SetMaterialShader(0, *_shader);
    }

    void Drawable3D::Draw(RayLib::Vector3 position, RayLib::Vector3 scale, RayLib::Color tint)
    {
        // rotation and angle are taken from the transform
        //_model.Draw(position, scale, tint);
        if (_texture)
            SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, *_texture);
        if (_shader)
            SetMaterialShader(0, *_shader);
        _model->DrawEx(position, RayLib::Vector3(0.0f, 1.0f, 0.0f), 0.0f, scale, tint);
    }

    void Drawable3D::SetMaterialTexture(int matIndex, int mapType, RayLib::Texture& text)
    {
        _model->SetMaterialTexture(matIndex, mapType, text);
    }

    void Drawable3D::SetMaterialShader(int matIndex, RayLib::Shader& shader)
    {
        _model->SetMaterialShader(matIndex, shader);
    }

    void Drawable3D::RotateModel(RayLib::Vector3 rotation)
    {
        _model->RotateModel(rotation);
    }

    RayLib::Model& Drawable3D::GetModel(void)
    {
        if (_model)
            return (*_model);
        throw Engine::Exception::EngineException("No model set");
    }

    RayLib::Shader& Drawable3D::GetShader(void)
    {
        if (_shader)
            return (*_shader);
        throw Engine::Exception::EngineException("No shader set");
    }

    RayLib::Texture& Drawable3D::GetTexture(void)
    {
        if (_texture)
            return (*_texture);
        throw Engine::Exception::EngineException("No texture set");
    }

    void Drawable3D::SetTexture(const std::string& path)
    {
        _texture = AssetCache::GetAsset<RayLib::Texture>(path);
        SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, *_texture);
    }

    void Drawable3D::SetModel(const std::string& path)
    {
        _model = AssetCache::GetAsset<RayLib::Model>(path);
    }

    void Drawable3D::SetShader(const std::string& path)
    {
        _shader = AssetCache::GetAsset<RayLib::Shader>(path);
        SetMaterialShader(0, *_shader);
    }

    std::ostream &Drawable3D::operator<<(std::ostream &os)
    {
        os << "<Drawable3D>";
        os << "<_model>" << AssetCache::GetAssetName(_model) << "</_model>";
        os << "<_texture>" << AssetCache::GetAssetName(_texture) << "</_texture>";
        os << "<_shader>" << AssetCache::GetAssetName(_shader) << "</_shader>";
        os << "</Drawable3D>";
        return (os);
    }

    boost::property_tree::ptree& Drawable3D::operator<<(boost::property_tree::ptree &ptree)
    {
        boost::property_tree::ptree drawable3DTree = ptree.get_child("Drawable3D");

        std::string texturePath = drawable3DTree.get<std::string>("_texture");
        std::string shaderPath = drawable3DTree.get<std::string>("_shader");
        std::string modelPath = drawable3DTree.get<std::string>("_model");

        if (modelPath != "")
            _model = AssetCache::GetAsset<RayLib::Model>(modelPath);
        if (texturePath != "")
            SetTexture(texturePath);
        if (shaderPath != "")
            SetShader(shaderPath);
        return (ptree);
    }


}
