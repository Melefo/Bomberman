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
        RayLib::Vector3 cubePosition;

        window->SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------

        //::Model model = LoadModel("../assets/castle/castle.obj");
        RayLib::Model model("../assets/castle/castle.obj");

        RayLib::Texture texture("../assets/castle/castle_diffuse.png");
        //Texture2D texture = LoadTexture("../assets/castle/castle_diffuse.png");    // Load model texture and set material
        //SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);  // Set model material map texture
        //model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;                 // Set map diffuse texture

        model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);

        camera.SetCameraMode(CAMERA_FREE);

        // Main game loop
        while (!window->WindowShouldClose())    // Detect window close button or ESC key
        {
            // Update

            camera.Update();
            // Draw
            //----------------------------------------------------------------------------------
            window->BeginDrawing();

            window->ClearBackground(RAYWHITE);

            camera.BeginMode();

            model.Draw(cubePosition, 1.0f, WHITE);
            //::DrawModelEx(model, cubePosition, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);

            //window->DrawCube(cubePosition, RayLib::Vector3(2.0f, 2.0f, 2.0f), RED);
            //window->DrawCubeWires(cubePosition, RayLib::Vector3(2.0f, 2.0f, 2.0f), MAROON);

            window->DrawGrid(20, 10.0f);

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
    // cf cet exemple pour drag & drop un model/texture et le charger à la volée
    //https://www.raylib.com/examples/web/models/loader.html?name=models_loading
    return (0);
}