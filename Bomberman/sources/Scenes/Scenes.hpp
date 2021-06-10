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
#include "TerrainGenerator.hpp"

namespace Scenes {
    void InitMap(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string> &map, const bool isEditor);
    void InitMainMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);
    void InitEditorMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);
    void InitEditor(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);
    void InitGame(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);
    void InitLoadingScreen(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);

    typedef void (*initSceneFunction)(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map);

    static std::map<std::string, initSceneFunction> scenesCtor = {std::make_pair<std::string, initSceneFunction>("MainMenu", &InitMainMenu),
                                                                  std::make_pair<std::string, initSceneFunction>("EditorMenu", &InitEditorMenu),
                                                                  std::make_pair<std::string, initSceneFunction>("Editor", &InitEditor),
                                                                  std::make_pair<std::string, initSceneFunction>("Game", &InitGame),
                                                                  std::make_pair<std::string, initSceneFunction>("LoadingScreen", &InitLoadingScreen)
                                                                 };
    
    void switchScene(ECS::Coordinator &coordinator, AssetManager &am, std::string &newScene);
}

#define BOX_SIZE 10

#endif /* !SCENES_HPP_ */
