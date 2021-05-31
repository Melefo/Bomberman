/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
#include "Window.hpp"
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

namespace Prototype
{
    void prototypeLoop()
    {
        std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");

        RayLib::Camera3D camera = RayLib::Camera3D();
        RayLib::Vector3 cubePosition;

        window->SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
        RayLib::Model model("../assets/castle/castle.obj");
        RayLib::Texture texture("../assets/castle/castle_diffuse.png");
        model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);
        camera.SetCameraMode(CAMERA_FREE);

        while (!window->WindowShouldClose())    // Detect window close button or ESC key
        {
            camera.Update();
            window->BeginDrawing();
            window->ClearBackground(RAYWHITE);
            camera.BeginMode();
            model.Draw(cubePosition, 1.0f, WHITE);
            window->DrawGrid(20, 10.0f);
            camera.EndMode();
            window->EndDrawing();
        }
    }
}

int main(void)
{
    Prototype::prototypeLoop();

    return (0);
}