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
#include "Destructible.hpp"
#include "Box.hpp"

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

            /**
             * @brief Load an entity from istream
             * 
             * @param is 
             * @return ECS::Entity& 
             */
            static ECS::Entity& LoadEntity(std::istream& is);
            /**
             * @brief Load an entity from property tree
             * 
             * @param ptree 
             * @return ECS::Entity& 
             */
            static ECS::Entity& LoadEntity(boost::property_tree::ptree &ptree);
            /**
             * @brief Load multiple entities from istream
             * 
             * @param is 
             */
            static void LoadEntities(std::istream& is);
            /**
             * @brief Load multiple entities from property tree
             * 
             * @param ptree 
             */
            static void LoadEntities(boost::property_tree::ptree &ptree);

            /**
             * @brief Add a transform component and populate it
             * 
             * @param entity 
             * @param ptree 
             */
            static void LoadTransform(ECS::Entity& entity, boost::property_tree::ptree &ptree);
            /**
             * @brief Add a renderer component and fill its info
             * 
             * @param entity 
             * @param ptree 
             */
            static void LoadRenderer(ECS::Entity& entity, boost::property_tree::ptree &ptree);
            /**
             * @brief Add a box collider and fill info
             * 
             * @param entity 
             * @param ptree 
             */
            static void LoadBoxCollider(ECS::Entity& entity, boost::property_tree::ptree &ptree);
            /**
             * @brief Add destructible component and fill info
             * 
             * @param entity 
             * @param ptree 
             */
            static void LoadDestructible(ECS::Entity& entity, boost::property_tree::ptree &ptree);

            /**
             * @brief Add physicsbody to entity
             * 
             */
            static void EntityLoader::LoadPhysicsBody(ECS::Entity& entity, boost::property_tree::ptree &ptree);

            static void LoadBox(ECS::Entity& entity, boost::property_tree::ptree &ptree);


        protected:
        private:
            static std::map<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>> _loadAbleComponents;

    };
}

#endif /* !ENTITYLOADER_HPP_ */
