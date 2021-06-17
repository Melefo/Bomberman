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

    // sphere mesh
    RayLib::Mesh sphereMesh(1.0f, 20, 20);
    // drawable
    ECS::Entity& sphereEntity = coordinator->CreateEntity();
    sphereEntity.AddComponent<Component::Transform>();
    sphereEntity.AddComponent<Component::Drawable3D>(sphereMesh);
    Component::Drawable3D& drawable = sphereEntity.GetComponent<Component::Drawable3D>();

    RayLib::Shader& shader = AssetCache::GetAsset<RayLib::Shader>("../assets/shaders/mask");
    drawable.SetMaterialShader(0, shader);

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