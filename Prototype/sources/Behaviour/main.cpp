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
#include "RayHitInfo.hpp"
#include <cmath>
#include "Coordinator.hpp"
#include "Entity.hpp"
#include "Transform.hpp"
#include "PhysicsBody.hpp"
#include "PhysicsSystem.hpp"
#include "Renderer.hpp"
#include "RenderSystem.hpp"

int main(void)
{
    ECS::Coordinator coordinator;
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");

    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<Prototype::Transform>();
    entity.AddComponent<Prototype::PhysicsBody>();
    entity.AddComponent<Prototype::Renderer>();

    coordinator.AddSystem<Prototype::PhysicsSystem>();
    coordinator.AddSystem<Prototype::RenderSystem>();

    entity.GetComponent<Prototype::Transform>().scale = RayLib::Vector3(0.05f, 0.05f, 0.05f);

    RayLib::Camera3D camera = RayLib::Camera3D();

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

        window->DrawGrid(20, 10.0f);
        camera.EndMode();
        window->EndDrawing();
    }
    return (0);
}