/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** main
*/

#include "Coordinator.hpp"
#include "Window.hpp"
#include "Camera.hpp"

int main(void)
{
    ECS::Coordinator coordinator;
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Bomberman");

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

        coordinator.Run();

        window->DrawGrid(20, 10.0f);
        camera.EndMode();
        window->EndDrawing();
    }
    return (0);
}