/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
#include "Window.hpp"
#include "Entity.hpp"
#include "Camera3D.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Input.hpp"
#include "BoundingBox.hpp"
#include "Ray.hpp"
#include "Physics3D.hpp"
#include "Mouse.hpp"
#include <cmath>
#include "Coordinator.hpp"
#include "Entity.hpp"
#include "Transform.hpp"
#include "PhysicsBody.hpp"
#include "PhysicsSystem.hpp"
#include "Renderer.hpp"
#include "RenderSystem.hpp"
#include "BehaviourSystem.hpp"
#include "PlayerMovement.hpp"
#include "UISystem.hpp"
#include "IBehaviour.hpp"
#include "BoxCollider.hpp"
#include "Draggable.hpp"

int main(void)
{
    ECS::Coordinator coordinator;
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Bomberman");
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 20.0f, -50.0f), RayLib::Vector3(0.0f, 10.0f, 0.0f));

    // ECS::Entity& cat = InitCat(coordinator);
    // ECS::Entity& button = InitButton(coordinator, camera);
    // ECS::Entity& box = InitBox(coordinator, camera);

    coordinator.AddSystem<Component::PhysicsSystem>();
    coordinator.AddSystem<Component::RenderSystem>();
    coordinator.AddSystem<Component::BehaviourSystem>();
    coordinator.AddSystem<Component::UISystem>();

    window->SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    camera.SetCameraMode(CAMERA_FREE);

    while (!window->WindowShouldClose())    // Detect window close button or ESC key
    {
        // update
        camera.Update();

        // draw
        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator.Update();

        camera.EndMode();
        window->EndDrawing();
    }
    return (0);
}