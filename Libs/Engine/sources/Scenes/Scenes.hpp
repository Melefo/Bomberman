/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Scenes
*/

#ifndef SCENES_HPP_
#define SCENES_HPP_

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
        /**
         * @brief Construct a new Scenes object
         * 
         */
        Scenes() = delete;
        /**
         * @brief Destroy the Scenes object
         * 
         */
        ~Scenes() = default;
        /**
         * @brief Construct a new Scenes object
         * 
         * @param other 
         */
        Scenes(const Scenes& other) = delete;
        /**
         * @brief Assignment operator
         * 
         * @param other 
         * @return Scenes& 
         */
        Scenes& operator=(const Scenes& other) = delete;

        /**
         * @brief Initialize the nbr of players of the game
         * 
         * @param entityFactory 
         * @param window 
         */
        static void InitNbrPlayers(EntityFactory& entityFactory, std::unique_ptr<RayLib::Window>& window);
        /**
         * @brief Initialize map game
         * 
         * @param coordinator 
         * @param camera 
         * @param isEditor 
         * @param deepness 
         */
        static void InitMap(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const bool isEditor, int deepness = 1);
        /**
         * @brief Initialize Main Menu
         * 
         * @param coordinator 
         * @param camera 
         */
        static void InitMainMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera);
        /**
         * @brief Initialize Editor Menu
         * 
         * @param coordinator 
         * @param camera 
         */
        static void InitEditorMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera);
        /**
         * @brief Initialize Editor
         * 
         * @param coordinator 
         * @param camera 
         */
        static void InitEditor(ECS::Coordinator& coordinator, RayLib::Camera3D& camera);
        /**
         * @brief Initialize Game
         * 
         * @param coordinator 
         * @param camera 
         */
        static void InitGame(ECS::Coordinator& coordinator, RayLib::Camera3D& camera);
        /**
         * @brief Initialize Game Over screen
         * 
         * @param coordinator 
         * @param camera 
         * @param endingMessage 
         */
        static void InitGameOver(ECS::Coordinator& coordinator, Component::Camera& camera, const std::string &endingMessage);
        /**
         * @brief Initialize Loading Screen
         * 
         * @param coordinator 
         * @param camera 
         */
        static void InitLoadingScreen(ECS::Coordinator& coordinator, RayLib::Camera3D& camera);
        /**
         * @brief Initialize Pause screen
         * 
         * @param coordinator 
         * @param camera 
         */
        static void InitPause(ECS::Coordinator& coordinator, RayLib::Camera3D& camera);
        /**
         * @brief Initialize Options screen
         * 
         * @param coordinator 
         * @param camera 
         */
        static void InitOptions(ECS::Coordinator& coordinator, RayLib::Camera3D& camera);

        /**
         * @brief switch current scene to another
         * 
         * @param coordinator 
         * @param newScene 
         */
        static void switchScene(ECS::Coordinator &coordinator, std::string &newScene);

        /**
         * @brief Map to initialize a scene by its name
         * 
         */
        static std::map<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>> scenesCtor;
    private:
};

#define BOX_SIZE 10

#endif /* !SCENES_HPP_ */
