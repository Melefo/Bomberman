/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Light
*/

#include "BasicLight.hpp"
#include "Vector4.hpp"

BasicLight::BasicLight(LightType type, RayLib::Vector3 position, RayLib::Color& color, const std::string& ShaderPath)
    : RayLib::Shader(ShaderPath+"base_lighting.vs", ShaderPath+"lighting.fs"),
    _type(static_cast<int>(type)), _position(position.getVector3()), _target(RayLib::Vector3().getVector3()), _color(color.getColor()),
    _typeLoc(GetLocation("light.type")), _posLoc(GetLocation("light.position")), _targetLoc(GetLocation("light.target")), _colorLoc(GetLocation("light.color"))
{
    UpdateValues();
}

void BasicLight::UpdateValues()
{
    RayLib::Vector3 position(_position.x, _position.y, _position.z);
    RayLib::Vector3 target(_target.x, _target.y, _target.z);
    RayLib::Vector4 shaderColor(_color.r/static_cast<float>(255),
        _color.g/static_cast<float>(255),
        _color.b/static_cast<float>(255),
        _color.a/static_cast<float>(255));

    SetValue(_typeLoc, &_type, SHADER_UNIFORM_VEC3);
    SetValue(_posLoc, position.getVector3(), SHADER_UNIFORM_VEC3);
    SetValue(_targetLoc, target.getVector3(), SHADER_UNIFORM_VEC3);
    SetValue(_colorLoc, shaderColor.getVector4(), SHADER_UNIFORM_VEC4);
}

::Vector3& BasicLight::GetPosition()
{
    return _position;
}
