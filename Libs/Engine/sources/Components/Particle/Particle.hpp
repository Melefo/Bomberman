/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Particle
*/

#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include "IBehaviour.hpp"
#include "Vector3.hpp"

namespace Component
{
    class Particle : public IBehaviour {
        public:
            Particle(float startSpeed=2.0f, float lifeTime=1.5f);
            ~Particle() override = default;

            /**
             * @brief Called once per cpu update, lerp color to transparent, kill
             * 
             * @param dt Time since last call to update
             */
            void Update(double dt, ECS::Entity& entity) override;
            /**
             * @brief Called every fixed seconds (CF coordinator)
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;

            /**
             * @brief Late update
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
            float _lifeTimer;
            float _speed;
            RayLib::Vector3 _direction;
    };
}

#endif /* !PARTICLE_HPP_ */
