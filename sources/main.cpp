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
#include "Input.hpp"

namespace Prototype
{
    void prototypeLoop()
    {
        //std::unique_ptr<RayLib::Window> window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
        RayLib::Window *window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
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
        delete(window);
    }

    void inputMove()
    {
        //std::unique_ptr<RayLib::Window> window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
        RayLib::Window *window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
        RayLib::Camera3D camera = RayLib::Camera3D();
        RayLib::Vector3 position;
        RayLib::Input input;

        float moveSpeed = 2.0f;

        window->SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
        RayLib::Model model("../assets/Cat_V2/cat.obj");
        RayLib::Texture texture("../assets/Cat_V2/banana.png");
        model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);
        camera.SetCameraMode(CAMERA_FREE);

        while (!window->WindowShouldClose())    // Detect window close button or ESC key
        {
            // update
            camera.Update();

            // draw
            window->BeginDrawing();
            window->ClearBackground(RAYWHITE);
            camera.BeginMode();

            RayLib::Vector2<float> movement = RayLib::Vector2<float>(input.GetHorizontalAxis(),
                                                                     input.GetVerticalAxis()) * moveSpeed;

            position.x += movement.x;
            position.z += movement.y;

            model.Draw(position, 0.1f, WHITE);
            window->DrawGrid(20, 10.0f);
            camera.EndMode();
            window->EndDrawing();
        }
        delete(window);
    }
}

int main(void)
{
    //Prototype::prototypeLoop();
    Prototype::inputMove();
    //Prototype::ObjDragAndDrop();

    // cf cet exemple pour drag & drop un model/texture et le charger à la volée
    //https://www.raylib.com/examples/web/models/loader.html?name=models_loading
    return (0);
}