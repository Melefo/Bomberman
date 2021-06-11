
#include "Coordinator.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "RenderSystem.hpp"
#include "Material.hpp"
#include "Entity.hpp"
#include "PhysicsSystem.hpp"
#include "Collider.hpp"
#include "SphereCollider.hpp"
#include "DropBomb.hpp"
#include "PlayerMovement.hpp"
#include "BehaviourSystem.hpp"
#include "UISystem.hpp"
#include <iostream>

void rayMarching(void)
{
    RayLib::Camera3D camera = RayLib::Camera3D(
        RayLib::Vector3(2.5f, 2.5f, 3.0f), // Position
        RayLib::Vector3(0.0f, 0.0f, 0.7f), // Target
        RayLib::Vector3(0.0f, 1.0f, 0.0f), // up
        65.0f); // Field of view
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
    RayLib::Shader shader("", "../Prototype/sources/Shaders/resources/glsl100/raymarching.fs"); // C fusion

    int vE = shader.GetLocation("viewEye");
    int vC = shader.GetLocation("viewCenter");
    int rT = shader.GetLocation("runTime");
    shader.SetValue<Vector2>(shader.GetLocation("resolution"), {800.0f, 450.0f}, SHADER_UNIFORM_VEC2);

    window->SetTargetFPS(60);
    camera.SetCameraMode(CAMERA_FREE);

    float runTime = 0.0f;
    while (!window->WindowShouldClose())
    {
        camera.Update();

        float deltaTime = GetFrameTime();
        runTime += deltaTime;

        RayLib::Vector3 cameraPos = camera.GetPosition();
        RayLib::Vector3 cameraTarget = camera.GetTarget();

        shader.SetValue(vE, cameraPos.getVector3(), SHADER_UNIFORM_VEC3);
        shader.SetValue(vC, cameraTarget.getVector3(), SHADER_UNIFORM_VEC3);
        shader.SetValue(rT, runTime, SHADER_UNIFORM_FLOAT);

        window->BeginDrawing();

        window->ClearBackground(RAYWHITE);

        shader.BeginMode();
        DrawRectangle(0, 0, 800, 450, WHITE);
        shader.EndMode();

        window->EndDrawing();
    }
}

int applyShaderToCube(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 20.0f, -50.0f), RayLib::Vector3(0.0f, 10.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");

    coordinator->AddSystem<Component::RenderSystem>();

    ECS::Entity& box = coordinator->CreateEntity();
    box.AddComponent<Component::Transform>();
    box.AddComponent<Component::Renderer>();
    box.GetComponent<Component::Transform>().scale = RayLib::Vector3(10.0f, 10.0f, 10.0f);
    box.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);

    ECS::Entity& box2 = coordinator->CreateEntity();
    box2.AddComponent<Component::Transform>();
    box2.AddComponent<Component::Renderer>();
    box2.GetComponent<Component::Transform>().scale = RayLib::Vector3(10.0f, 10.0f, 10.0f);
    box2.GetComponent<Component::Transform>().position = RayLib::Vector3(20.0f, 0.0f, 0.0f);

    RayLib::Texture texture("../Prototype/sources/Shaders/resources/cube_texture.png");
    RayLib::Shader shader("", "../Prototype/sources/Shaders/resources/glsl100/grayscale.fs");

    box.GetComponent<Component::Renderer>().GetModel().SetMaterialShader(0, shader);
    box.GetComponent<Component::Renderer>().GetModel().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);

    box2.GetComponent<Component::Renderer>().GetModel().SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, texture);

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

ECS::Entity& InitBox(ECS::Coordinator& coordinator)
{
    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::PhysicsBody>();
    entity.AddComponent<Component::Renderer>("../assets/Cat_V2/test.iqm", "../Prototype/sources/Shaders/resources/cube_texture.png");
    entity.AddComponent<Component::Collider, Component::SphereCollider>(entity, RayLib::Vector3(), 7.5f);

    entity.AddComponent<Component::IBehaviour, Component::PlayerMovement>(entity, 0.5f);

    entity.GetComponent<Component::Transform>().rotation = RayLib::Vector3(-90.0f, 0.0f, 0.0f);

    entity.AddComponent<Component::IBehaviour, Component::DropBomb>(entity);

    return (entity);
}

int customBoxMain(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 20.0f, -50.0f), RayLib::Vector3(0.0f, 10.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");

    InitBox(*coordinator.get());

    coordinator->AddSystem<Component::PhysicsSystem>();
    coordinator->AddSystem<Component::RenderSystem>();
    coordinator->AddSystem<Component::BehaviourSystem>();
    coordinator->AddSystem<Component::UISystem>(camera);

    window->SetTargetFPS(60);
    camera.SetCameraMode(CAMERA_FREE);

    while (!window->WindowShouldClose())
    {
        camera.Update();

        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator->Run();

        window->DrawGrid(20, 10.0f);
        camera.EndMode();
        window->EndDrawing();
    }
    return (0);
}

int main(void)
{
    //rayMarching();
    //applyShaderToCube();
    //customBoxMain();
}
