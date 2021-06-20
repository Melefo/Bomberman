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
#include "RangeBoost.hpp"

class EntityFactory {
    public:
        EntityFactory(ECS::Coordinator& coordinator);
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
        ECS::Entity& createButton(const std::string& texturePath = "../assets/Default_texture.png", bool lerp = true);
        /**
         * @brief Create a TextBox object
         *
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createTextBox(int maxLength, const std::string& fontPath, float size, float spacing = 0.0f, RayLib::Color color = BLACK);
        
        /**
         * @brief Create a Wall object
         * 
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createWall(RayLib::Vector3 pos);

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
        ECS::Entity& createBox(RayLib::Vector3 pos, const int level, const bool draggable);

        /**
         * @brief Create a Player object
         * 
         * @param Engine::playerkeys& keys used to controller the player
         * @param int To set the tag with the nbr of the player (J1, J2, J3...)
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createPlayer(Engine::playerkeys& keys, int nbrOfThePlayer);

        /**
         * @brief Create a basic HUD part
         * 
         * @param Component::AController & the controller the HUD is linked to
         * @param int The n th player. So the function knows where to put the hud
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createBaseHUD(int nbrOfThePlayer);

        /**
         * @brief Create a HUD part with a text
         * 
         * @param Component::AController & the controller the HUD is linked to
         * @param int The n th player. So the function knows where to put the hud
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createHUDText(Component::AController &controller, int nbrOfThePlayer);

        /**
         * @brief Create a AI object
         * 
         * @return ECS::Entity& 
         */
        ECS::Entity& createAI();

        /**
         * @brief Create a HUD part with a bonus icon
         * 
         * @param Component::AController & the controller the HUD is linked to
         * @param int The n th player. So the function knows where to put the hud
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createHUDBonusIcon(Component::AController &controller, int nbrOfThePlayer, const std::string &path, float &timer);

        /**
         * @brief Create a HUD part with a bonus bar
         * 
         * @param Component::AController & the controller the HUD is linked to
         * @param int The n th player. So the function knows where to put the hud
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createHUDBonusBar(Component::AController &controller, int nbrOfThePlayer, const std::string &type, float &timer);

         /**
         * @brief Create a Text object
         * 
         * @return ECS::Entity::& The entity created
         */
        ECS::Entity& createText(const std::string& content, const std::string& fontPath, float size, float spacing=0.0f, RayLib::Color color = BLACK);

        /**
         * @brief Create a random Pick Up bonus
         * 
         * @return ECS::Entity& 
         */
        ECS::Entity& createPickUp(void);

        /**
         * @brief Create a Speed Pick Up object
         * 
         * @return ECS::Entity& 
         */
        ECS::Entity& createSpeedPickUp(void);
        /**
         * @brief Create a Range Pick Up object
         * 
         * @return ECS::Entity& 
         */
        ECS::Entity& createRangePickUp(void);
        /**
         * @brief Create a Cooldown Pick Up object
         * 
         * @return ECS::Entity& 
         */
        ECS::Entity& createCooldownPickUp(void);

        /**
         * @brief Create a Bomb object
         * 
         * @param radius (how many squares should the explosion span)
         * @param type 
         * @return ECS::Entity& 
         */
        ECS::Entity& createBomb(float radius, Component::Explosion::ExplosionType type);

        ECS::Entity& createCamera(RayLib::Camera3D &camera, const std::string& musicPath = "");

        ECS::Entity& createParticle(const std::string& texturePath, RayLib::Vector2<float> minMaxSize,
                                    RayLib::Vector2<int> minMaxSides, float startSpeed=2.0f,
                                    float lifeTime=1.5f);
  
        ECS::Entity& createFloor(RayLib::Vector2<float> mapSize);

    protected:
    private:
        ECS::Coordinator& _coordinator;
        std::vector<std::function<ECS::Entity&(void)>> _pickupFunctions;
};

#endif /* !ENTITYFACTORY_HPP_ */
