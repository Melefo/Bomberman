/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** DropBomb
*/

#ifndef DROPBOMB_HPP_
#define DROPBOMB_HPP_

#include "IBehaviour.hpp"
#include "Input.hpp"
#include "PhysicsBody.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Explosion.hpp"
#include "BoxCollider.hpp"
#include "Transform.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Destructible.hpp"

namespace Component
{
    /**
     * @brief Behaviour for players or AI allowing to drop a bomb upon pressing a key
     * 
     */
    class DropBomb : public IBehaviour {
        public:
            /**
             * @brief Construct a new Drop Bomb object
             * 
             * @param attatchedEntity 
             * @param coordinator 
             * @param dropBombKey Key to press
             * @param dropDelay Cooldown for bomb-dropping
             */
            DropBomb(ECS::Entity& attatchedEntity, int dropBombKey=KEY_X, float dropDelay=2.5f);
            /**
             * @brief Destroy the Drop Bomb object
             * 
             */
            ~DropBomb() override = default;
            /**
             * @brief Construct a new Drop Bomb object
             * 
             * @param other 
             */
            DropBomb(const DropBomb& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return DropBomb& 
             */
            DropBomb& operator=(const DropBomb& other) = default;

            // ! à mettre dans une factory
            /**
             * @brief Function to create a bomb, belongs in an entity factory
             * 
             * @param position 
             * @param explosionType 
             * @param radius 
             */
            void InstantiateBomb(RayLib::Vector3 position,
                                 Explosion::ExplosionType explosionType=Explosion::ExplosionType::CIRCLE,
                                 float radius=1.0f);

            /**
             * @brief Updates timers and check if dropbomb key is pressed
             * 
             * @param dt 
             */
            void Update(double dt) override;
            /**
             * @brief FixedUpdate
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;

            std::ostream& operator<<(std::ostream& stream) override;

        protected:
        private:
            /**
             * @brief Input class to check the keypress
             * 
             */
            RayLib::Input _input;
            /**
             * @brief Reference t oentity
             * 
             */
            ECS::Entity& _entity;
            /**
             * @brief Singleton coordinator reference (instantiation)
             * 
             */
            std::unique_ptr<ECS::Coordinator>& _coordinator;
            /**
             * @brief Transform component, to instantiate bomb at position
             * 
             */
            Transform& _transform;
            /**
             * @brief Bomb drop input key
             * 
             */
            int _bombKey;
            /**
             * @brief Bomb cooldown
             * 
             */
            float _dropDelay;
            /**
             * @brief Cooldown timer
             * 
             */
            float _timeToDrop;
            /**
             * @brief Reference to window singleton to get frametime
             * 
             */
            std::unique_ptr<RayLib::Window>& _window;
    };
}

#endif /* !DROPBOMB_HPP_ */
