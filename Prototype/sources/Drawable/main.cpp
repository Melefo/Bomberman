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
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 50.0f, 0.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 0.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(1920, 1080), "Bomberman");

    coordinator->AddSystem<Component::RenderSystem>();

    //Component::ButtonCallbacks::GenerateBackgroundMap();

    EntityFactory factory(*coordinator.get(), camera);

    for (int i = 0; i < 100; i++) {

        RayLib::Shader& shader = AssetCache::GetAsset<RayLib::Shader>("../assets/shaders/mask");
        RayLib::Texture& text = AssetCache::GetAsset<RayLib::Texture>("../assets/Box/Box_texture.png");

        ECS::Entity& box = factory.createBox(0, false);
        box.GetComponent<Component::Drawable3D>().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, text);
        //box.GetComponent<Component::Drawable3D>().SetMaterialShader(0, shader);
    }

    window->SetTargetFPS(60);
    window->SetExitKey(KEY_ESCAPE);
    while (!window->WindowShouldClose() && !coordinator->CloseWindow)
    {
        camera.Update();

        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator->Run();

        window->DrawGrid(100.0f, 1.0f);

        camera.EndMode();
        window->EndDrawing();
    }

    return (0);
}