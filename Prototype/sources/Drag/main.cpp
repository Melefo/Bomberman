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
#include "RayCollision.hpp"
#include <cmath>

namespace Prototype
{
    void DragDrop()
    {
        std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");

        RayLib::Camera3D camera = RayLib::Camera3D();
        RayLib::Vector3 position;
        RayLib::Vector3 scale = RayLib::Vector3(1.0f, 1.0f, 1.0f);

        bool selected = false;
        RayLib::Ray ray;                    // Picking line ray

        window->SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
        camera.SetCameraMode(CAMERA_FREE);


        RayLib::BoundingBox bounds = RayLib::BoundingBox(RayLib::Vector3(), RayLib::Vector3());
        bounds.InitFromCube(position, scale);

        while (!window->WindowShouldClose())    // Detect window close button or ESC key
        {
            // update
            camera.Update();
            ray = camera.GetMouseRay(RayLib::Mouse::GetPosition());

            if (RayLib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (!selected)
                {
                    // Check collision between ray and box
                    selected = RayLib::Physics3D::CheckCollision(ray, bounds);
                }
            }
            if (RayLib::Mouse::IsButtonPressed(MOUSE_BUTTON_RIGHT))
                selected = false;

            // if selected, move with mouse flat on plane (y = 0)
            if (selected) {
                RayLib::RayCollision hitInfo = RayLib::Physics3D::CheckCollision(ray, 0.0f);

                if (hitInfo.HasHit()) {
                    // snap position
                    position = hitInfo.GetPosition();
                    position = RayLib::Vector3(round(position.x), position.y, round(position.z));
                }
            }
            bounds.InitFromCube(position, scale);

            // draw
            window->BeginDrawing();
            window->ClearBackground(RAYWHITE);
            camera.BeginMode();

            if (selected) {
                window->DrawCube(position, scale, RED);

                window->DrawCubeWires(position, scale + RayLib::Vector3(0.2f, 0.2f, 0.2f), GREEN);
            } else {
                window->DrawCube(position, scale, GRAY);
            }

            window->DrawGrid(10, 1.0f);
            camera.EndMode();
            window->EndDrawing();
        }
        //delete(window);
    }
}

int main(void)
{
    Prototype::DragDrop();

    // !next step:
        // press D_KEY to duplicate obj
        // press E_KEY to delete OBJ
        // use example below to drag and drop models/textures

    // cf cet exemple pour drag & drop un model/texture et le charger à la volée
    //https://www.raylib.com/examples/web/models/loader.html?name=models_loading
    return (0);
}