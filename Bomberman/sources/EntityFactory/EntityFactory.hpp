/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** EntityFactory
*/

#ifndef ENTITYFACTORY_HPP_
#define ENTITYFACTORY_HPP_

#include "Coordinator.hpp"
#include "Camera3D.hpp"

class EntityFactory {
    public:
        EntityFactory(ECS::Coordinator& coordinator, RayLib::Camera3D& camera);
        ~EntityFactory() = default;

        /**
         * @brief Create a new Entity object
         * 
         * @tparam T 
         * @tparam TArgs 
         * @param args 
         */
        template<typename T, typename... TArgs>
        void createEntity(TArgs&&... args) {
            std::make_unique<T>(std::forward<TArgs>(args)...);
        };
        
        /**
         * @brief Create a Button object
         * 
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createButton(const std::string& texturePath="../assets/models/cube/def_text.png");
        
        /**
         * @brief Create a Wall object
         * 
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createWall();
        
        /**
         * @brief Create a Box object
         * 
         * @param level The level of the box
         * '1' => Weak
         * '2' => Medium
         * '3' => Strong
         * @param draggable Is the box draggable
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createBox(const int level, const bool draggable);
        
        /**
         * @brief Create a Player object
         * 
         * @param playerColor The color of the player (...colors?)
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createPlayer(const std::string &playerColor);

         /**
         * @brief Create a Text object
         * 
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createText(const std::string& content="Enter text here");

    protected:
    private:
        ECS::Coordinator& _coordinator;
        RayLib::Camera3D& _camera;
};

#endif /* !ENTITYFACTORY_HPP_ */
