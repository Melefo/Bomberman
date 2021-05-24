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

    void example()
    {
        // Initialization
        //--------------------------------------------------------------------------------------
        const int screenWidth = 800;
        const int screenHeight = 450;

        InitWindow(screenWidth, screenHeight, "raylib [models] example - models loading");

        // Define the camera to look into our 3d world
        Camera camera = { 0 };
        camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
        camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                                // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

        Model model = LoadModel("../assets/castle/castle.obj");                 // Load model
        Texture2D texture = LoadTexture("../assets/castle/castle_diffuse.png"); // Load model texture
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;                 // Set map diffuse texture

        Vector3 position = { 0.0f, 0.0f, 0.0f };                // Set model position

        BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);  // Set model bounds

        // NOTE: bounds are calculated from the original size of the model,
        // if model is scaled on drawing, bounds must be also scaled

        SetCameraMode(camera, CAMERA_FREE);     // Set a free camera mode

        bool selected = false;          // Selected object flag

        SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------

        // Main game loop
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            // Update
            //----------------------------------------------------------------------------------
            UpdateCamera(&camera);

            // Load new models/textures on drag&drop
            if (IsFileDropped())
            {
                int count = 0;
                char **droppedFiles = GetDroppedFiles(&count);

                if (count == 1) // Only support one file dropped
                {
                    if (IsFileExtension(droppedFiles[0], ".obj") ||
                        IsFileExtension(droppedFiles[0], ".gltf") ||
                        IsFileExtension(droppedFiles[0], ".iqm"))       // Model file formats supported
                    {
                        UnloadModel(model);                     // Unload previous model
                        model = LoadModel(droppedFiles[0]);     // Load new model
                        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set current map diffuse texture

                        bounds = GetMeshBoundingBox(model.meshes[0]);

                        // TODO: Move camera position from target enough distance to visualize model properly
                    }
                    else if (IsFileExtension(droppedFiles[0], ".png"))  // Texture file formats supported
                    {
                        // Unload current model texture and load new one
                        UnloadTexture(texture);
                        texture = LoadTexture(droppedFiles[0]);
                        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
                    }
                }

                ClearDroppedFiles();    // Clear internal buffers
            }

            // Select model on mouse click
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // Check collision between ray and box
                if (CheckCollisionRayBox(GetMouseRay(GetMousePosition(), camera), bounds)) selected = !selected;
                else selected = false;
            }
            //----------------------------------------------------------------------------------

            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

                ClearBackground(RAYWHITE);

                BeginMode3D(camera);

                    DrawModel(model, position, 1.0f, WHITE);        // Draw 3d model with texture

                    DrawGrid(20, 10.0f);         // Draw a grid

                    if (selected) DrawBoundingBox(bounds, GREEN);   // Draw selection box

                EndMode3D();

                DrawText("Drag & drop model to load mesh/texture.", 10, GetScreenHeight() - 20, 10, DARKGRAY);
                if (selected) DrawText("MODEL SELECTED", GetScreenWidth() - 110, 10, 10, GREEN);

                DrawText("(c) Castle 3D model by Alberto Cano", screenWidth - 200, screenHeight - 20, 10, GRAY);

                DrawFPS(10, 10);

            EndDrawing();
            //----------------------------------------------------------------------------------
        }

        // De-Initialization
        //--------------------------------------------------------------------------------------
        UnloadTexture(texture);     // Unload texture
        UnloadModel(model);         // Unload model

        CloseWindow();              // Close window and OpenGL context
        //--------------------------------------------------------------------------------------

    }
}

int main(void)
{
    Prototype::prototypeLoop();
    //Prototype::example();
    return (0);
}