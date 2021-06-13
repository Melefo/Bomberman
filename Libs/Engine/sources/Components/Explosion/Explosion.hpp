/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Explosion
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Vector3.hpp"
#include "IBehaviour.hpp"
#include "Window.hpp"
#include "CollisionSystem.hpp"
#include "Transform.hpp"
#include "Destructible.hpp"
#include "Exceptions.hpp"
#include "AssetManager.hpp"

namespace Component
{
    /**
     * @brief Explosion/Bomb component
     * 
     */
    class Explosion : public IBehaviour {
        public:
            /**
             * @brief Enum to determine bomb shape
             * 
             */
            enum class ExplosionType
            {
                CIRCLE,
                CROSS,
                VERTICAL,
                HORIZONTAL,
            };
            /**
             * @brief Construct a new Explosion object
             * 
             * @param entity 
             * @param radius 
             * @param type 
             * @param power 
             * @param timer Time in seconds before the physics check goes out
             */
            Explosion(ECS::Entity& entity, float radius=1.0f,
                      Explosion::ExplosionType type=Explosion::ExplosionType::CROSS,
                      unsigned int power=1,
                      float timer=3.0f);
            /**
             * @brief Destroy the Explosion object
             * 
             */
            ~Explosion() override = default;
            /**
             * @brief Construct a new Explosion object
             * 
             * @param other 
             */
            Explosion(const Explosion& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return Explosion& 
             */
            Explosion& operator=(const Explosion& other) = default;

            /**
             * @brief Updates timers and explodes
             * 
             * @param dt 
             */
            void Update(double dt, ECS::Entity& entity) override;
            /**
             * @brief Fixed Update
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;

            /**
             * @brief 
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

            /**
             * @brief Explosion type
             * 
             */
            Explosion::ExplosionType type;
            /**
             * @brief Bomb's power (i.e. damage)
             * 
             */
            unsigned int power;
        protected:
        private:
            /**
             * @brief Bomb's area of effect
             * 
             */
            float _radius;
            /**
             * @brief Time in seconds before explosion
             * 
             */
            float _explosionTimer;
            /**
             * @brief Window reference to debug radius
             * 
             */
            std::unique_ptr<RayLib::Window>& _window;
            /**
             * @brief refence to self in order to dispose after exploding
             * 
             */
            ECS::Entity& _myEntity;
            /**
             * @brief Transform position for collisions
             * 
             */
            Transform& _transform;
            /**
             * @brief Coordinator, to pass to collisionsystem
             * 
             */
            std::unique_ptr<ECS::Coordinator>& _coordinator;

    };
}

#endif /* !EXPLOSION_HPP_ */
