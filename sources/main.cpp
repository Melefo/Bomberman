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

namespace Prototype
{
    void prototypeLoop()
    {
    // Initialization
        //--------------------------------------------------------------------------------------
        //const int screenWidth = 800;
        //const int screenHeight = 450;

        //std::unique_ptr<RayLib::Window> window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
        RayLib::Window *window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");

        RayLib::Camera3D camera = RayLib::Camera3D();

        Vector3 cubePosition;


        window->SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------

        // Main game loop
        while (!window->WindowShouldClose())    // Detect window close button or ESC key
        {
            // Update

            // Draw
            //----------------------------------------------------------------------------------
            window->BeginDrawing();

            window->ClearBackground(WHITE);

            camera.BeginMode();

            window->DrawCube(cubePosition, RayLib::Vector3(2.0f, 2.0f, 2.0f), RED);
            window->DrawCubeWires(cubePosition, RayLib::Vector3(2.0f, 2.0f, 2.0f), MAROON);

            window->DrawGrid(10, 1.0f);

            camera.EndMode();

            //DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

            //DrawFPS(10, 10);

            window->EndDrawing();
            //----------------------------------------------------------------------------------
        }

        delete(window);
        // De-Initialization
        //--------------------------------------------------------------------------------------
        //--------------------------------------------------------------------------------------

    }
}

int main(void)
{
    Prototype::prototypeLoop();
    return (0);
}