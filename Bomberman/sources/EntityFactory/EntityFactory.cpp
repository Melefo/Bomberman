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
#include "Movement.hpp"
#include "DropBomb.hpp"
#include "EntityFactory.hpp"
#include "Scenes.hpp"
#include "Animator.hpp"
#include "SphereCollider.hpp"
#include "Texture.hpp"
#include "Image.hpp"
#include "TextUI.hpp"
#include "Font.hpp"
#include "PlayerInputs.hpp"
#include "SpeedBoost.hpp"
#include "CoolDownBoost.hpp"
#include "Explosion.hpp"
#include "Box.hpp"
#include "TextBox.hpp"
#include "TextBoxCallback.hpp"

EntityFactory::EntityFactory(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
    : _coordinator(coordinator), _camera(camera)
{
    _pickupFunctions.push_back(std::bind(&EntityFactory::createSpeedPickUp, this));
    _pickupFunctions.push_back(std::bind(&EntityFactory::createRangePickUp, this));
    _pickupFunctions.push_back(std::bind(&EntityFactory::createCooldownPickUp, this));
}

ECS::Entity& EntityFactory::createButton(const std::string& assetName)
{
    ECS::Entity &entity = _coordinator.CreateEntity();

    entity.AddComponent<Component::IUIObject, Component::Button>();
    entity.AddComponent<Component::Renderer>(assetName);
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::ButtonCallbacks>(entity);

    return (entity);
}

ECS::Entity& EntityFactory::createTextBox(int maxLength, const std::string& fontPath, float size, float spacing, RayLib::Color color)
{
    ECS::Entity& entity = _coordinator.CreateEntity();

    entity.AddComponent<Component::Renderer>();
    entity.AddComponent<Component::IUIObject, Component::TextBox>(maxLength, fontPath, size, spacing, color, false, true);
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::TextBoxCallback>(entity);

    return (entity);
}

ECS::Entity& EntityFactory::createText(const std::string& content, const std::string& fontPath, float size, float spacing)
{
    ECS::Entity &entity = _coordinator.CreateEntity();

    entity.AddComponent<Component::Renderer>();
    entity.AddComponent<Component::IUIObject, Component::TextUI>(content, fontPath, size, spacing);
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    return (entity);
}

ECS::Entity& EntityFactory::createWall()
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("Wall");
    entity.AddComponent<Component::Transform>(RayLib::Vector3(-20.0f, 0.0f, 0.0f), RayLib::Vector3(-90, 0, 0), RayLib::Vector3(2.5f, 2.5f, 2.5f));
    entity.AddComponent<Component::Renderer>("Wall");
    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));

    return (entity);
}

ECS::Entity& EntityFactory::createBox(const int, const bool draggable)
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("Box");
    entity.AddComponent<Component::Transform>();
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(5, 5, 5);
    entity.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);
    entity.AddComponent<Component::Renderer>("Box");
    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    //entity.AddComponent<Component::Destructible>(entity, 1);
    entity.AddComponent<Component::Box>(entity, 1);

    if (draggable)
        entity.AddComponent<Component::IBehaviour, Component::Draggable>(entity, _camera);

    return (entity);
}

ECS::Entity& EntityFactory::createPlayer(Engine::playerkeys& keys)
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("Player");
    entity.AddComponent<Component::Transform>(RayLib::Vector3(), RayLib::Vector3(), RayLib::Vector3(6, 6, 6));
    entity.AddComponent<Component::PhysicsBody>();
    entity.AddComponent<Component::Renderer>("Player");
    entity.AddComponent<Component::Animator>(entity, "Player", "Idle");
    entity.AddComponent<Component::Collider, Component::SphereCollider>(entity, RayLib::Vector3(), 4.0f);

    entity.AddComponent<Component::IBehaviour, Component::PlayerInputs>(entity, keys.movementInput, keys.actionKey);

    entity.GetComponent<Component::Transform>().rotation = RayLib::Vector3(-90.0f, 0.0f, 0.0f);
    entity.AddComponent<Component::Destructible>(entity, 1);
    return (entity);
}

ECS::Entity& EntityFactory::createRangePickUp(void)
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("RangePickUp");
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::Renderer>("RangePickUp");
    entity.AddComponent<Component::IBehaviour, Component::RangeBoost>(entity, 5.0f);
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(5.0f, 5.0f, 5.0f);
    return (entity);
}

ECS::Entity& EntityFactory::createCooldownPickUp(void)
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("CoolDownPickUp");
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::Renderer>("CoolDownPickUp");
    entity.AddComponent<Component::IBehaviour, Component::CoolDownBoost>(entity, 5.0f);
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(5.0f, 5.0f, 5.0f);
    return (entity);
}

ECS::Entity& EntityFactory::createSpeedPickUp(void)
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("SpeedPickUp");
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::Renderer>("SpeedPickUp");
    entity.AddComponent<Component::IBehaviour, Component::SpeedBoost>(entity, 5.0f);
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(5.0f, 5.0f, 5.0f);
    return (entity);
}

ECS::Entity& EntityFactory::createPickUp(void)
{
    int index = rand() % (_pickupFunctions.size() - 1);
    ECS::Entity &entity = _pickupFunctions[index]();
    return (entity);
}

ECS::Entity& EntityFactory::createBomb(float radius, Component::Explosion::ExplosionType type)
{
    ECS::Entity& entity = _coordinator.CreateEntity();

    entity.SetTag("Bomb");
    entity.AddComponent<Component::Transform>(RayLib::Vector3(), RayLib::Vector3(), RayLib::Vector3(BOX_SIZE, BOX_SIZE, BOX_SIZE));
    entity.AddComponent<Component::Renderer>("Bomb");
    //! si on spawn une bombe sur le joueur, on est bloqués
    //entity.AddComponent<Collider, BoxCollider>(entity, _coordinator);
    entity.AddComponent<Component::IBehaviour, Component::Explosion>(entity, radius, type);
    return (entity);
}

ECS::Entity& EntityFactory::createCamera(void)
{
    ECS::Entity& entity = _coordinator.CreateEntity();

    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 100.0f, -50.0f));
    entity.AddComponent<Component::IBehaviour, Component::Camera>(entity, _camera);
    return (entity);
}
