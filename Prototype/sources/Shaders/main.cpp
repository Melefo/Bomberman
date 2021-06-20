/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** main
*/

#include "Coordinator.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "RenderSystem.hpp"
#include "Entity.hpp"
#include "PhysicsSystem.hpp"
#include "Collider.hpp"
#include "DropBomb.hpp"
#include "Model.hpp"
#include "BehaviourSystem.hpp"
#include "UISystem.hpp"
#include "RenderTexture.hpp"
#include "BasicLight.hpp"
#include "AmbientShader.hpp"
#include "raymath.h"
#include "TerrainShader.hpp"
#include "AssetCache.hpp"
#include "Drawable3D.hpp"
#include <rlgl.h>
#include <iostream>

int applyShaderToCube(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 20.0f, -50.0f), RayLib::Vector3(0.0f, 10.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");

    coordinator->AddSystem<Component::RenderSystem>();

    std::shared_ptr<RayLib::Texture> boxTexture = AssetCache::GetAsset<RayLib::Texture>("../Prototype/sources/Shaders/resources/cube_texture.png");
    std::shared_ptr<RayLib::Shader> boxShader = AssetCache::GetAsset<RayLib::Shader>("../Prototype/sources/Shaders/resources/glsl/grayscale");

    RayLib::Mesh cubeMesh = RayLib::Mesh(RayLib::Vector3(10.0f, 10.0f, 10.0f));

    ECS::Entity& box = coordinator->CreateEntity();
    box.AddComponent<Component::Transform>();
    box.AddComponent<Component::Drawable3D>(cubeMesh);
    box.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);
    box.GetComponent<Component::Drawable3D>().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, *boxTexture);
    box.GetComponent<Component::Drawable3D>().SetMaterialShader(0, *boxShader);

    ECS::Entity& box2 = coordinator->CreateEntity();
    box2.AddComponent<Component::Transform>();
    box2.AddComponent<Component::Drawable3D>(cubeMesh);
    box2.GetComponent<Component::Transform>().position = RayLib::Vector3(20.0f, 0.0f, 0.0f);
    box2.GetComponent<Component::Drawable3D>().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, *boxTexture);

    //RayLib::Texture texture("../Prototype/sources/Shaders/resources/cube_texture.png");

    //assetManagerRef->getAssetFromName("box").getModel().SetMaterialShader(0, shader);
    //assetManagerRef->getAssetFromName("box").getModel().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);
    //box.GetComponent<Component::Renderer>().GetModel().SetMaterialShader(0, shader);
    //box.GetComponent<Component::Renderer>().GetModel().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);

    //assetManagerRef->getAssetFromName("box2").getModel().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);

    window->SetTargetFPS(60);
    camera.SetCameraMode(CAMERA_FREE);

    while (!window->WindowShouldClose())
    {
        camera.Update();

        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator->Run();

        camera.EndMode();
        window->EndDrawing();
    }
    return (0);
}

int allBlue(void)
{
    int screenWidth = 1920;
    int screenHeight = 1080;

    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
    //std::unique_ptr<AssetManager>& assetManagerRef = AssetManager::GetInstance();

    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 20.0f, -50.0f), RayLib::Vector3(0.0f, 10.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(screenWidth, screenHeight), "Prototype");

    coordinator->AddSystem<Component::RenderSystem>();
    RayLib::Mesh cube(RayLib::Vector3(10.0f, 10.0f, 10.0f));

    ECS::Entity& box = coordinator->CreateEntity();
    box.AddComponent<Component::Transform>();
    box.AddComponent<Component::Drawable3D>(cube);
    box.GetComponent<Component::Drawable3D>().SetTexture("../Prototype/sources/Shaders/resources/cube_texture.png");
    box.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);

    ECS::Entity& box2 = coordinator->CreateEntity();
    box2.AddComponent<Component::Transform>();
    box2.AddComponent<Component::Drawable3D>(cube);
    box2.GetComponent<Component::Drawable3D>().SetTexture("../Prototype/sources/Shaders/resources/cube_texture.png");
    box2.GetComponent<Component::Transform>().position = RayLib::Vector3(20.0f, 0.0f, 0.0f);

    //RayLib::Texture texture("../Prototype/sources/Shaders/resources/cube_texture.png");
    // RayLib::Color color(216, 240, 240, 255);
    RayLib::Color color(222, 70, 0, 100);
    AmbientShader ambientShader(color, "../assets/shaders/");

    //assetManagerRef->getAssetFromName("box").getModel().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);
    //assetManagerRef->getAssetFromName("box2").getModel().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);

    // By activating next line (Adding entity to the ambient shader), it will add it on display.
    // Otherwise its texture will remain the same
    // assetManagerRef->getAssetFromName("box2").getModel().SetMaterialShader(0, ambientShader);

    window->SetTargetFPS(60);
    camera.SetCameraMode(CAMERA_FREE);

    RayLib::RenderTexture target(screenWidth, screenHeight);

    while (!window->WindowShouldClose())
    {
        camera.Update();

        window->BeginDrawing();
            window->ClearBackground(RAYWHITE);
            target.BeginMode();
                window->ClearBackground(RAYWHITE);
                camera.BeginMode();
                    coordinator->Run();
                camera.EndMode();
            target.EndMode();
            ambientShader.BeginMode();
                target.DrawTexture();
            ambientShader.EndMode();

        window->EndDrawing();
    }
    return (0);
}

int basic_lighting_remastered(void)
{
    std::string protoResourcesPath = "../Prototype/sources/Shaders/resources/";
    std::string protoShadersPath = "../assets/shaders/";
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic lighting");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 2.0f, 6.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    // Load models
    Model modelA = LoadModelFromMesh(GenMeshTorus(0.4f, 1.0f, 16, 32));
    Model modelB = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
    Model modelC = LoadModelFromMesh(GenMeshSphere(0.5f, 32, 32));

    // Load models texture
    Texture texture = LoadTexture(std::string(protoResourcesPath+"texel_checker.png").c_str());

    // Assign texture to default model material
    modelA.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    modelB.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    modelC.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    RayLib::Vector3 position(4.0f, 2.0f, 4.0f);
    RayLib::Vector3 target;
    RayLib::Color whiteColor(WHITE);
    BasicLight light(BasicLight::LightType::LIGHT_POINT, position, whiteColor, protoShadersPath);

    // Get some shader loactions
    light.SetLoc(SHADER_LOC_MATRIX_MODEL, "matModel");
    light.SetLoc(SHADER_LOC_VECTOR_VIEW, "viewPos");

    // ambient light level
    float ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    light.SetValue(light.GetLocation("ambient"), ambient, SHADER_UNIFORM_VEC4);

    float angle = 6.282f;

    // All models use the same shader
    modelA.materials[0].shader = light.GetShader();
    modelB.materials[0].shader = light.GetShader();
    modelC.materials[0].shader = light.GetShader();

    SetCameraMode(camera, CAMERA_ORBITAL);  // Set an orbital camera mode

    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())            // Detect window close button or ESC key
    {

        UpdateCamera(&camera);              // Update camera

        // Make the lights do differing orbits
        angle -= 0.02f;
        light.GetPosition().x = cosf(angle)*4.0f;
        light.GetPosition().z = sinf(angle)*4.0f;

        light.UpdateValues();

        // Rotate the torus
        modelA.transform = MatrixMultiply(modelA.transform, MatrixRotateX(-0.025f));
        modelA.transform = MatrixMultiply(modelA.transform, MatrixRotateZ(0.012f));

        // Update the light shader with the camera view position
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        light.SetValue(light.GetShader().locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // Draw the three models
                DrawModel(modelA, Vector3Zero(), 1.0f, WHITE);
                DrawModel(modelB, (Vector3){-1.6f,0.0f,0.0f}, 1.0f, WHITE);
                DrawModel(modelC, (Vector3){ 1.6f,0.0f,0.0f}, 1.0f, WHITE);

                // Draw markers to show where the lights are
                DrawSphereEx(light.GetPosition(), 0.2f, 8, 8, WHITE);

                DrawGrid(10, 1.0f);

            EndMode3D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(modelA);        // Unload the modelA
    UnloadModel(modelB);        // Unload the modelB
    UnloadModel(modelC);        // Unload the modelC

    UnloadTexture(texture);     // Unload the texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

int mapFloorShader()
{
    std::string protoShadersPath = "../assets/shaders/";

    const int screenWidth = 800;
    const int screenHeight = 450;
    
    const int boxSize = 10;

    RayLib::Vector2<float> mapSize(13*boxSize, 17*boxSize);

    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 20.0f, -50.0f), RayLib::Vector3(0.0f, 10.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(screenWidth, screenHeight), "Prototype");

    coordinator->AddSystem<Component::RenderSystem>();
    
    RayLib::Mesh planeMesh(mapSize.x, mapSize.y, 1, 1);

    RayLib::Color floorColor(68, 194, 64, 255);
    RayLib::Texture texture(RayLib::Image(RayLib::Vector2<int>(static_cast<int>(mapSize.x), static_cast<int>(mapSize.y)), floorColor.getColor()));

    std::shared_ptr<RayLib::Shader> shader = AssetCache::GetAsset<RayLib::Shader>("../assets/shaders/terrainShader");
    
    ECS::Entity& plane = coordinator->CreateEntity();
    plane.AddComponent<Component::Transform>();
    plane.AddComponent<Component::ModelShader, TerrainShader>("../assets/shaders/terrainShader", mapSize);
    plane.AddComponent<Component::Drawable3D>(planeMesh);
    Component::Drawable3D& planeDrawable = plane.GetComponent<Component::Drawable3D>();
    planeDrawable.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);
    planeDrawable.SetMaterialShader(0, *shader);

    window->SetTargetFPS(60);
    camera.SetCameraMode(CAMERA_FREE);

    while (!window->WindowShouldClose())
    {
        camera.Update();

        window->BeginDrawing();

            window->ClearBackground(RAYWHITE);
            camera.BeginMode();
            window->DrawGrid(20, 10.0f);
            coordinator->Run();
            camera.EndMode();

        window->EndDrawing();
    }
    return (0);
}

int glowShader()
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 10.0f, 0.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 1.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(1920, 1080), "Bomberman");

    coordinator->AddSystem<Component::RenderSystem>();

    // sphere mesh
    RayLib::Mesh sphereMesh(1.0f, 20, 20);
    // drawable
    ECS::Entity& sphereEntity = coordinator->CreateEntity();
    sphereEntity.AddComponent<Component::Transform>();
    sphereEntity.AddComponent<Component::Drawable3D>(sphereMesh);
    Component::Drawable3D& drawable = sphereEntity.GetComponent<Component::Drawable3D>();

    std::shared_ptr<RayLib::Shader> shader = AssetCache::GetAsset<RayLib::Shader>("../assets/shaders/glow");
    drawable.SetMaterialShader(0, *shader);

    window->SetTargetFPS(60);
    window->SetExitKey(KEY_ESCAPE);
    camera.SetCameraMode(CAMERA_FREE);
    while (!window->WindowShouldClose() && !coordinator->CloseWindow)
    {
        camera.Update();
        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator->Run();

        window->DrawGrid(10, 1.0f);

        camera.EndMode();
        window->EndDrawing();
    }

    return (0);
}

int skyboxShader()
{
    std::string protoShadersPath = "../assets/shaders/";

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    RayLib::Vector2<float> mapSize(10000, 10000);

    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 20.0f, -50.0f), RayLib::Vector3(0.0f, 10.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(screenWidth, screenHeight), "Prototype");

    coordinator->AddSystem<Component::RenderSystem>();
    
    RayLib::Mesh cubeMesh(RayLib::Vector3(1.0f, 1.0f, 1.0f));

    std::shared_ptr<RayLib::Shader> sbShader = AssetCache::GetAsset<RayLib::Shader>("../assets/shaders/skybox");
    
    ECS::Entity& cubeMap = coordinator->CreateEntity();
    cubeMap.AddComponent<Component::Transform>();
    cubeMap.AddComponent<Component::Drawable3D>(cubeMesh);
    cubeMap.GetComponent<Component::Drawable3D>().SetMaterialShader(0, *sbShader);

    RayLib::Mesh cuboidMesh(RayLib::Vector3(10.0f, 10.0f, 10.0f));
    ECS::Entity& cube = coordinator->CreateEntity();
    cube.AddComponent<Component::Transform>();
    cube.AddComponent<Component::Drawable3D>(cuboidMesh);

    sbShader->SetValue(sbShader->GetLocation("environmentMap"), MATERIAL_MAP_CUBEMAP, SHADER_UNIFORM_INT);
    sbShader->SetValue(sbShader->GetLocation("doGamma"), 0, SHADER_UNIFORM_INT);
    sbShader->SetValue(sbShader->GetLocation("vflipped"), 1, SHADER_UNIFORM_INT);

    std::shared_ptr<RayLib::Shader> cmShader = AssetCache::GetAsset<RayLib::Shader>("../assets/shaders/cubemap");

    cmShader->SetValue(cmShader->GetLocation("equirectangularMap"), 0, SHADER_UNIFORM_INT);

    RayLib::Texture panorama("../assets/SkyBox/skybox.png");
    RayLib::Texture texture(*cmShader, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

    cubeMap.GetComponent<Component::Drawable3D>().SetMaterialTexture(0, MATERIAL_MAP_CUBEMAP, texture);

    window->SetTargetFPS(60);
    camera.SetCameraMode(CAMERA_FIRST_PERSON);

    while (!window->WindowShouldClose())
    {
        camera.Update();

        window->BeginDrawing();

            window->ClearBackground(RAYWHITE);
            camera.BeginMode();
            rlDisableBackfaceCulling();
            rlDisableDepthMask();
            coordinator->Run();
            rlEnableBackfaceCulling();
            rlEnableDepthMask();
            camera.EndMode();

        window->EndDrawing();
    }
    return (0);
}

int main(void)
{
    // applyShaderToCube();
    //allBlue();
    // basic_lighting_remastered();
    // mapFloorShader();
    // glowShader();
    skyboxShader();
}
