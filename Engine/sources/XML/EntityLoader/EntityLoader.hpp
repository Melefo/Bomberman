/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** EntityLoader
*/

#ifndef ENTITYLOADER_HPP_
#define ENTITYLOADER_HPP_

#include "Entity.hpp"
#include "IXMLSerializable.hpp"
#include "Coordinator.hpp"
#include "Transform.hpp"
#include "Renderer.hpp"

namespace Serialization
{
    class EntityLoader {
        public:
            /**
             * @brief Construct a new Entity Loader object
             * 
             */
            EntityLoader() = default;
            /**
             * @brief Destroy the Entity Loader object
             * 
             */
            ~EntityLoader() = default;

            static ECS::Entity& LoadEntity(std::istream& is);
            static ECS::Entity& LoadEntity(boost::property_tree::ptree &ptree);

            static void LoadTransform(ECS::Entity& entity, boost::property_tree::ptree &ptree);
            static void LoadRenderer(ECS::Entity& entity, boost::property_tree::ptree &ptree);

        protected:
        private:
            static std::map<std::string, void (*)(ECS::Entity&, boost::property_tree::ptree&)> _loadAbleComponents;

    };
}

#endif /* !ENTITYLOADER_HPP_ */
