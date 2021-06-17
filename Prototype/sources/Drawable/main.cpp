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

int main(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 10.0f, 10.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 1.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(1920, 1080), "Bomberman");

    coordinator->AddSystem<Component::RenderSystem>();

    ECS::Entity& sphere = coordinator->CreateEntity();
    RayLib::Mesh mesh(1.0f, 20, 20);
    sphere.AddComponent<Component::Drawable3D>(mesh);
    sphere.AddComponent<Component::Transform>();

    ECS::Entity& bomb = coordinator->CreateEntity();
    bomb.AddComponent<Component::Transform>();

    bomb.AddComponent<Component::Drawable3D>("../assets/bomb/Bomb_model.iqm");
    RayLib::Texture bombTexture("../assets/bomb/Bomb_texture.png");
    bomb.GetComponent<Component::Drawable3D>().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, bombTexture);

    // create mesh (inherits from iDrawable)

    window->SetTargetFPS(60);
    window->SetExitKey(KEY_ESCAPE);
    while (!window->WindowShouldClose() && !coordinator->CloseWindow)
    {
        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator->Run();

        camera.EndMode();
        window->EndDrawing();
    }

    return (0);
}