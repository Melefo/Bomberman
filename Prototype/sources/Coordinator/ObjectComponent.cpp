/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** OjectComponent
*/

#include "ObjectComponent.hpp"

ObjectComponent::ObjectComponent() :
model("../assets/Cat_V2/cat.obj"), texture("../assets/Cat_V2/banana.png")
{
    position = RayLib::Vector3(rand() % 20, rand() % 20, rand() % 20);
    size = 0.01f;
    model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);
}