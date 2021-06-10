/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** main
*/

#include "Coordinator.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Scenes.hpp"
#include "TerrainGenerator.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include "BehaviourSystem.hpp"
#include "UISystem.hpp"
#include "AssetManager.hpp"

int main(void)
{
    ECS::Coordinator coordinator;
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Bomberman");
    AssetManager AM;

    RayLib::Camera3D camera = RayLib::Camera3D();

    window->SetTargetFPS(60);
    camera.SetCameraMode(CAMERA_FREE);
    TerrainGenerator map(8);

    //AM.loadAssets(coordinator.GetEntities());

    coordinator.AddSystem<Component::PhysicsSystem>();
    coordinator.AddSystem<Component::RenderSystem>();
    coordinator.AddSystem<Component::BehaviourSystem>();
    coordinator.AddSystem<Component::UISystem>(camera);

    while (!window->WindowShouldClose())    // Detect window close button or ESC key
    {
        if (coordinator.GetEntities().size() == 0) {
            Scenes::scenesCtor[coordinator.getCurrentScene()](coordinator, camera, map.getMap());

        }
        // update
        camera.Update();

        // draw
        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator.Run();
        if (window->WindowShouldClose())
            break;

        window->DrawGrid(20, 10.0f);
        camera.EndMode();
        window->EndDrawing();
    }
    return (0);
}
