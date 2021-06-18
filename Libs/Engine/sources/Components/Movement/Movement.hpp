/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Movement
*/

#ifndef Movement_HPP_
#define Movement_HPP_

#include "IBehaviour.hpp"
#include "Input.hpp"
#include "PhysicsBody.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Transform.hpp"
#include <algorithm>
#include "Animator.hpp"
#include "Window.hpp"
#include "Physics2D.hpp"

namespace Component
{
    /**
     * @brief Behaviour script responsible for moving an entity
     * 
     */
    class Movement : public IBehaviour {
        public:
            /**
             * @brief Construct a new Player Movement object
             * 
             * @param attatchedEntity 
             * @param moveSpeed 
             */
            Movement(ECS::Entity& attatchedEntity, float moveSpeed = 0.5f, float maxSpeed=1.0f);

            /**
             * @brief Destroy the Player Movement object
             * 
             */
            ~Movement() override = default;
            /**
             * @brief Construct a new Player Movement object
             * 
             * @param other 
             */
            Movement(const Movement& other) = default;
            /**
             * @brief Assignement operator
             * 
             * @param other 
             * @return Movement& 
             */
            Movement& operator=(const Movement& other) = default;

            /**
             * @brief Used to sample the input
             * 
             * @param dt 
             */
            void Update(double dt, ECS::Entity& entity) override;
            /**
             * @brief Used to modify the velocity regularly
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

            void SlipperyCollisions();

            bool CheckCollidersPos(std::vector<std::reference_wrapper<Collider>> colliders,
                                   RayLib::Vector3 position,
                                   std::vector<std::string> colMask = {});

            void BoostSpeed(float bonusSpeed=3.0f, float time=20.0f);

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

            /**
             * @brief Direction used to direct velocity
             * 
             */
            RayLib::Vector3 direction;
        protected:
        private:
            /**
             * @brief Ref to entity for transform/physics
             * 
             */
            ECS::Entity& _entity;

            /**
             * @brief Is the entity colliding or not (i.e. can it move)
             * 
             */
            bool _colliding;
            /**
             * @brief Speed multiplier
             * 
             */
            float _speed;
            /**
             * @brief starting speed
             * 
             */
            float _startSpeed;
            /**
             * @brief Time for which a boost is applied
             * 
             */
            float _bonusTime;

            float _maxSpeed;

            std::vector<std::string> _collisionMask;

    };
}

#endif /* !Movement_HPP_ */
