/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Prototype
*/

#ifndef PROTOTYPE_HPP_
#define PROTOTYPE_HPP_

#include <vector>
#include <string>
#include <memory>
#include "Model.hpp"

namespace Prototype
{
    class Entity {
        public:
            Entity(const std::string& modelPath, RayLib::Vector3 position=RayLib::Vector3());
            ~Entity();

            RayLib::Model& getModel();
            RayLib::Vector3& getPosition();

            // move ?

        protected:
        private:
            std::unique_ptr<RayLib::Model> model;
            RayLib::Vector3 position;
    };
}
#endif /* !PROTOTYPE_HPP_ */
