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
#include "Explosion.hpp"
#include "Camera.hpp"
#include "GameConfiguration.hpp"

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
        ECS::Entity& createButton(const std::string& texturePath="../assets/Default_texture.png");
        
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
        ECS::Entity& createPlayer(Engine::playerkeys& keys);

         /**
         * @brief Create a Text object
         * 
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createText(const std::string& content="Enter text here");
        /**
         * @brief Create a random Pick Up bonus
         * 
         * @return ECS::Entity& 
         */
        ECS::Entity& createPickUp(void);

        /**
         * @brief Create a Bomb object
         * 
         * @param radius (how many squares should the explosion span)
         * @param type 
         * @return ECS::Entity& 
         */
        ECS::Entity& createBomb(float radius, Component::Explosion::ExplosionType type);

        ECS::Entity& createCamera(void);

    protected:
    private:
        ECS::Coordinator& _coordinator;
        RayLib::Camera3D& _camera;
};

#endif /* !ENTITYFACTORY_HPP_ */
