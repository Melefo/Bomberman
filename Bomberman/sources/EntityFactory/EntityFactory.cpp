/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** EntityFactory
*/

#include "UISystem.hpp"
#include "Transform.hpp"
#include "Button.hpp"
#include "ButtonCallbacks.hpp"
#include "BoxCollider.hpp"
#include "Renderer.hpp"
#include "Draggable.hpp"
#include "Destructible.hpp"
#include "PlayerMovement.hpp"
#include "DropBomb.hpp"
#include "EntityFactory.hpp"
#include "Scenes.hpp"
#include "Animator.hpp"
#include "SphereCollider.hpp"
#include "Texture.hpp"
#include "Image.hpp"

EntityFactory::EntityFactory(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
    : _coordinator(coordinator), _camera(camera)
{
}

ECS::Entity& EntityFactory::createButton(const std::string& texturePath)
{
    ECS::Entity &entity = _coordinator.CreateEntity();

    entity.AddComponent<Component::IUIObject, Component::Button>(texturePath);
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::ButtonCallbacks>(entity);

    return (entity);
}

ECS::Entity& EntityFactory::createWall()
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("Wall");
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::Renderer>();
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(BOX_SIZE, BOX_SIZE, BOX_SIZE);
    entity.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);
    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));

    return (entity);
}

ECS::Entity& EntityFactory::createBox(const int level, const bool draggable)
{
    RayLib::Texture texture("assets/Blue.jpg");// TEMPORARY

    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("Box");
    entity.AddComponent<Component::Transform>();
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(BOX_SIZE, BOX_SIZE, BOX_SIZE);
    entity.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);
    entity.AddComponent<Component::Renderer>("", "assets/Blue.jpg");
    //entity.GetComponent<Component::Renderer>().GetModel().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture); // TEMPORARY
    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::Destructible>(entity, 1);
    if (draggable)
        entity.AddComponent<Component::IBehaviour, Component::Draggable>(entity, _camera);

    return (entity);
}

ECS::Entity& EntityFactory::createPlayer(const std::string &playerColor)
{(void)playerColor;
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::PhysicsBody>();
    // entity.AddComponent<Component::Renderer>("assets/Player/" + playerColor + "Player.obj", "assets/Player/" + playerColor + "Player.png");
    entity.AddComponent<Component::Renderer>("../assets/BoxMan/guy.iqm", "../assets/BoxMan/guytex.png");
    entity.AddComponent<Component::Animator>("../assets/BoxMan/guyanim.iqm", "Idle");
    // entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::Collider, Component::SphereCollider>(entity, RayLib::Vector3(1), 7.5f);
    entity.AddComponent<Component::IBehaviour, Component::PlayerMovement>(entity, 0.5f);
    entity.GetComponent<Component::Transform>().rotation = RayLib::Vector3(-90.0f, 0.0f, 0.0f);
    entity.AddComponent<Component::IBehaviour, Component::DropBomb>(entity);
    //entity.AddComponent<Component::Destructible>(entity, 1);

    return (entity);
}
