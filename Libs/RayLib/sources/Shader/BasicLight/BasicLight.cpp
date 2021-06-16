/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Light
*/

#include "BasicLight.hpp"
#include "Vector4.hpp"

BasicLight::BasicLight(LightType type, RayLib::Vector3 position, RayLib::Color& color, const std::string& ShaderPath)
    : RayLib::Shader(ShaderPath+"base_lighting.vs", ShaderPath+"lighting.fs")
{
    _type = static_cast<int>(type);
    _position = position.getVector3();
    _target = RayLib::Vector3().getVector3();
    _color = color.getColor();

    std::string typeName("light.type");
    std::string posName("light.position");
    std::string targetName("light.target");
    std::string colorName("light.color");

    _typeLoc = GetLocation(typeName);
    _posLoc = GetLocation(posName);
    _targetLoc = GetLocation(targetName);
    _colorLoc = GetLocation(colorName);

    UpdateValues();
}

void BasicLight::UpdateValues()
{
    float position[3] = {_position.x, _position.y, _position.z};
    float target[3] = {_target.x, _target.y, _target.z};
    float color[4] = {
        _color.r/static_cast<float>(255),
        _color.g/static_cast<float>(255),
        _color.b/static_cast<float>(255),
        _color.a/static_cast<float>(255)};

    SetValue(_typeLoc, &_type, SHADER_UNIFORM_VEC3);
    SetValue(_posLoc, position, SHADER_UNIFORM_VEC3);
    SetValue(_targetLoc, &target, SHADER_UNIFORM_VEC3);
    SetValue(_colorLoc, color, SHADER_UNIFORM_VEC4);
}

::Vector3& BasicLight::GetPosition()
{
    return _position;
}
