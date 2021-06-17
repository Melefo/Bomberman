/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics2D
*/

#ifndef PHYSICS2D_HPP_
#define PHYSICS2D_HPP_


#include <raylib.h>
#include "PhysacBody.hpp"
#include "Entity.hpp"
#include "Coordinator.hpp"
#include "Vector3.hpp"
#include "Collider.hpp"
#include "EngineExceptions.hpp"

namespace Engine
{
    class Physics2D {
        public:
            Physics2D() = default;
            ~Physics2D() = default;

            static bool CheckCollision(RayLib::PhysacBody& body1, RayLib::PhysacBody& body2);

            bool IsColliding(ECS::Entity& body, std::vector<std::string> colmask);
            /**
             * @brief Call IsColliding with a temporary position
             * 
             * @param center 
             * @return true 
             * @return false 
             */
            static bool IsCollidingAtPosition(ECS::Entity& body, RayLib::Vector2<float> center, std::vector<std::string> colmask);

            void DrawLines(ECS::Entity& body);

            /**
             * @brief Get the Entity we are colliding with, throws an error if no entity collides
             * 
             * @return ECS::Entity& 
             */
            static ECS::Entity& GetCollision(ECS::Entity& body, std::vector<std::string> colmask);

            /**
             * @brief Get the Collision Position object
             * 
             * @param center 
             * @return ECS::Entity& 
             */
            static ECS::Entity& GetCollisionPosition(ECS::Entity& body, RayLib::Vector2<float> center, std::vector<std::string> colmask);

            static void InitPhysics(void);
            static void ClosePhysics(void);

        protected:
        private:
    };
}

#endif /* !PHYSICS2D_HPP_ */
