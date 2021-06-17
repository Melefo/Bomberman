/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BoxCollider
*/

#ifndef BOXCOLLIDER_HPP_
#define BOXCOLLIDER_HPP_

#include "Collider.hpp"
#include "Vector3.hpp"

namespace Component
{
    class BoxCollider : public Collider {
        public:
            BoxCollider(ECS::Entity& attatchedEntity,
                        RayLib::Vector2<float> position,
                        std::vector<std::string> colMask,
                        RayLib::Vector2<float> scale=RayLib::Vector2<float>(1.0f, 1.0f));
            ~BoxCollider() = default;
            /**
             * @brief Construct a new Box Collider object
             * 
             * @param other 
             */
            BoxCollider(const BoxCollider& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return BoxCollider& 
             */
            BoxCollider& operator=(const BoxCollider& other) = default;

            RayLib::PhysacBody& GetPhysacBody() override;

            void UpdateBody();

        protected:
        private:
            RayLib::PhysacBody _myBody;
    };
}

#endif /* !BOXCOLLIDER_HPP_ */
