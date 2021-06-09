/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
#include "Coordinator.hpp"
#include "Transform.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include "BehaviourSystem.hpp"
#include "UISystem.hpp"
#include "CollisionSystem.hpp"
#include "BoxCollider.hpp"
#include "PlayerMovement.hpp"
#include "DropBomb.hpp"
#include "Button.hpp"
#include "ButtonCallbacks.hpp"
#include "Draggable.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "SphereCollider.hpp"
#include "GameConfigurator.hpp"

#include "TerrainGenerator.hpp"

#define BOX_SIZE 10


ECS::Entity& InitCat(ECS::Coordinator& coordinator)
{
    // cat
    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<Component::Transform>(RayLib::Vector3(30, 0, 30));
    entity.AddComponent<Component::PhysicsBody>();
    entity.AddComponent<Component::Renderer>("../assets/BoxMan/guy.iqm", "../assets/BoxMan/guytex.png");
    entity.AddComponent<Component::Animator>("../assets/BoxMan/guyanim.iqm", "Idle");
    //entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::Collider, Component::SphereCollider>(entity, RayLib::Vector3(), 4.0f);

    entity.AddComponent<Component::IBehaviour, Component::PlayerMovement>(entity, 0.5f);

    entity.GetComponent<Component::Transform>().rotation = RayLib::Vector3(-90.0f, 0.0f, 0.0f);

    entity.AddComponent<Component::IBehaviour, Component::DropBomb>(entity);

    //entity.AddComponent<Prototype::Destructible>(entity, 1);

    return (entity);
}

ECS::Entity& InitButton(ECS::Coordinator& coordinator)
{
    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<Component::IUIObject, Component::Button>();
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 20.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::ButtonCallbacks>(entity);

    Component::Button& button = entity.GetComponent<Component::Button>();

    button.AddCallback(std::bind(&Component::ButtonCallbacks::StaticCallback));

    return (entity);
}

ECS::Entity& InitBox(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    ECS::Entity& entity = coordinator.CreateEntity();
    entity.AddComponent<Component::Transform>();
    //entity.AddComponent<Prototype::PhysicsBody>();
    entity.AddComponent<Component::Renderer>();
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(10.0f, 10.0f, 10.0f);
    entity.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);

    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::IBehaviour, Component::Draggable>(entity, camera);
    entity.AddComponent<Component::Destructible>(entity, 1);

    return (entity);
}

ECS::Entity& InitCamera(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, Component::Transform& target)
{
    ECS::Entity& entity = coordinator.CreateEntity();

    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 100.0f, 0.0f));
    entity.AddComponent<Component::IBehaviour, Component::Camera>(entity, camera, target.position);

    return (entity);
}

ECS::Entity& createWall(ECS::Coordinator &_coordinator)
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

ECS::Entity& createBox(ECS::Coordinator &_coordinator, int level, const bool draggable, RayLib::Camera3D _camera)
{
    RayLib::Texture texture("assets/Blue.jpg");// TEMPORARY

    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("Box");
    entity.AddComponent<Component::Transform>();
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(BOX_SIZE, BOX_SIZE, BOX_SIZE);
    entity.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);
    entity.AddComponent<Component::Renderer>();
    entity.GetComponent<Component::Renderer>().GetModel().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture); // TEMPORARY
    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::Destructible>(entity, 1);
    if (draggable)
        entity.AddComponent<Component::IBehaviour, Component::Draggable>(entity, _camera);

    return (entity);
}

void InitMap(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string> &map, const bool isEditor)
    {
        for (size_t y = 0; y < map.size(); y++) {
            for (size_t x = 0; x < map[y].size(); x++) {
                if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::OWALL)
                || map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::INWALL)) {
                    ECS::Entity& wall = createWall(coordinator);
                    wall.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
                } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::WEAKBOX)) {
                    ECS::Entity& box = createBox(coordinator, 1, isEditor ? true : false, camera);
                    box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
                } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::MEDIUMBOX)) {
                    ECS::Entity& box = createBox(coordinator,2, isEditor ? true : false, camera);
                    box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
                } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::STRONGBOX)) {
                    ECS::Entity& box = createBox(coordinator, 3, isEditor ? true : false,camera);
                    box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
                }
            }
        }
    }

int main(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    //! camera pos and target determined by component
    //! attention le 3e arg: world up est important
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 0.0f, 0.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 0.0f, 1.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
    TerrainGenerator map(2);

    ECS::Entity& cat = InitCat(*coordinator.get());
    ECS::Entity& button = InitButton(*coordinator.get());
    /*ECS::Entity& box = */InitBox(*coordinator.get(), camera);
        InitMap(*coordinator.get(), camera, map.getMap(), true);            // ajoute la default map en fond

    //! game manager for drag and drop
    ECS::Entity& gameManager = coordinator->CreateEntity();
    gameManager.AddComponent<Component::IBehaviour, Component::GameConfigurator>();
    //!

    InitCamera(*coordinator.get(), camera, cat.GetComponent<Component::Transform>());

    coordinator->AddSystem<Component::PhysicsSystem>();
    coordinator->AddSystem<Component::RenderSystem>();
    coordinator->AddSystem<Component::BehaviourSystem>();
    coordinator->AddSystem<Component::UISystem>(camera);

    window->SetTargetFPS(60);
    //camera.SetCameraMode(CAMERA_FREE);

    while (!window->WindowShouldClose())
    {
        /*if (coordinator->GetEntities().size() == 0)
            Scenes::scenesCtor[coordinator->getCurrentScene()](*(coordinator.get()), camera);*/
        //camera.Update();

        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator->Run();

        window->DrawGrid(20, 10.0f);
        camera.EndMode();
        window->EndDrawing();
    }
    return (0);
}