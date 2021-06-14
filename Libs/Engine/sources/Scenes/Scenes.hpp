/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Scenes
*/

#ifndef SCENES_HPP_
#define SCENES_HPP_

#include "AssetManager.hpp"
#include "Coordinator.hpp"
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
#include "GameConfiguration.hpp"
#include "TerrainGenerator.hpp"

class Scenes {
    public:
        static void InitNbrPlayers(EntityFactory& entityFactory, std::unique_ptr<RayLib::Window>& window);
        static void InitMap(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string> &map, const bool isEditor);
        static void InitMainMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);
        static void InitEditorMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);
        static void InitEditor(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);
        static void InitGame(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);
        static void InitLoadingScreen(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);

        static void switchScene(ECS::Coordinator &coordinator, AssetManager &am, std::string &newScene);

        static std::map<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)>> scenesCtor;
    private:
};

#define BOX_SIZE 10

#endif /* !SCENES_HPP_ */
