/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** Scenes
*/

#include "Camera3D.hpp"
#include "Entity.hpp"
#include "Coordinator.hpp"
#include "IUIObject.hpp"
#include "Transform.hpp"
#include "IBehaviour.hpp"
#include "Button.hpp"
#include "Image.hpp"
#include "ButtonCallbacks.hpp"
#include "Renderer.hpp"
#include "EntityFactory.hpp"
#include "Ray.hpp"
#include "TerrainGenerator.hpp"
#include "Scenes.hpp"


std::map<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)>> Scenes::scenesCtor =
    {std::pair<std::string, initSceneFunction>("MainMenu", &InitMainMenu),
    std::pair<std::string, initSceneFunction>("EditorMenu", &InitEditorMenu),
    std::pair<std::string, initSceneFunction>("Editor", &InitEditor),
    std::pair<std::string, initSceneFunction>("Game", &InitGame)};

void Scenes::InitMap(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string> &map, const bool isEditor)
{
    EntityFactory entityFactory(coordinator, camera);

    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::OWALL)
            || map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::INWALL)) {
                ECS::Entity& wall = entityFactory.createWall();
                wall.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
            } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::WEAKBOX)) {
                ECS::Entity& box = entityFactory.createBox(1, isEditor ? true : false);
                box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
            } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::MEDIUMBOX)) {
                ECS::Entity& box = entityFactory.createBox(2, isEditor ? true : false);
                box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
            } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::STRONGBOX)) {
                ECS::Entity& box = entityFactory.createBox(3, isEditor ? true : false);
                box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
            }
        }
    }
}

void Scenes::InitMainMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& defaultMap)
{
    EntityFactory entityFactory(coordinator, camera);

    ECS::Entity &entityQuit = entityFactory.createButton("../assets/buttons/quitGameButton.png");
    //entityQuit.GetComponent<Component::Transform>().position = RayLib::Vector3(0.0f, 0.0f, 0.0f);
    entityQuit.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::QuitWindow));
    /*ECS::Entity &entityPlayer = */entityFactory.createPlayer("blue");

    //InitMap(coordinator, camera, defaultMap, 0);            // ajoute la default map en fond
}

void Scenes::InitEditorMenu(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)
{
}

void Scenes::InitEditor(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& selMap)
{
    EntityFactory entityFactory(coordinator, camera);

    ECS::Entity &entityAddBox = entityFactory.createButton();
    entityAddBox.GetComponent<Component::Transform>().position = RayLib::Vector3(0.0f, 0.0f, 0.0f);
    entityAddBox.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::CreateBox));
    (void)selMap;
}

void Scenes::InitGame(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map)
{
    EntityFactory entityFactory(coordinator, camera);
    //InitMap(coordinator, camera, map, 0);

    ECS::Entity &entityPlayer = entityFactory.createPlayer("blue");
    (void)entityPlayer;
    (void)map;
}

