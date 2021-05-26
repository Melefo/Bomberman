/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** OjectComponent
*/

#include "OjectComponent.hpp"

OjectComponent::OjectComponent() :
model("/home/gabriel/YEP/B-YEP-400-NAN-4-1-indiestudio-victor.trencic/assets/Cat_V2/cat.obj"), texture("/home/gabriel/YEP/B-YEP-400-NAN-4-1-indiestudio-victor.trencic/assets/Cat_V2/banana.png")
{
    position = RayLib::Vector3(rand() % 20, rand() % 20, rand() % 20);
    size = 0.01f;
    model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);
}