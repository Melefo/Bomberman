/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** main
*/

#include "Coordinator.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "Drawable3D.hpp"
#include "RenderSystem.hpp"
#include <iostream>
#include "Mesh.hpp"
#include "Vector2.hpp"
#include "AssetCache.hpp"
#include "Shader.hpp"
#include "ButtonCallbacks.hpp"
#include "EntityFactory.hpp"

int main(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 10.0f, 0.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 1.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(1920, 1080), "Bomberman");

    coordinator->AddSystem<Component::RenderSystem>();

    ECS::Entity& entity1 = coordinator->CreateEntity();
    entity1.AddComponent<Component::Transform>(RayLib::Vector3(5.0f, 0.0f, 0.0f));
    entity1.AddComponent<Component::Drawable3D>("../assets/bomb/Bomb_model.iqm", "../assets/bomb/Bomb_texture.png");

    ECS::Entity& entity2 = coordinator->CreateEntity();
    entity2.AddComponent<Component::Transform>(RayLib::Vector3(-5.0f, 0.0f, 0.0f));
    entity2.AddComponent<Component::Drawable3D>("../assets/bomb/Bomb_model.iqm", "../assets/castle/castle_diffuse.png");

    window->SetTargetFPS(60);
    window->SetExitKey(KEY_ESCAPE);
    camera.SetCameraMode(CAMERA_FREE);
    while (!window->WindowShouldClose() && !coordinator->CloseWindow)
    {
        camera.Update();
        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator->Run();

        window->DrawGrid(10, 1.0f);

        camera.EndMode();
        window->EndDrawing();
    }

    return (0);
}