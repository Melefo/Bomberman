/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** main
*/

#include "Coordinator.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include <iostream>

int main(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 10.0f, 10.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 1.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(1920, 1080), "Bomberman");

    // create mesh
    // create drawable (from mesh)

    // create mesh (inherits from idrawable)

    window->SetTargetFPS(60);
    window->SetExitKey(KEY_ESCAPE);
    while (!window->WindowShouldClose() && !coordinator->CloseWindow)
    {
        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();
        coordinator->Run();

        // drawable.Draw()

        // mesh(idrawable).Draw()

        camera.EndMode();
        window->EndDrawing();
    }

    // drawable
        // take mesh
        // take file
        // set texture
        // contains model

    // mesh class ()
        // polymorphic to create multiple things

    return (0);
}