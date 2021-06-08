/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** EntitySerializer
*/

#ifndef ENTITYSERIALIZER_HPP_
#define ENTITYSERIALIZER_HPP_

#include "XMLGenerator.hpp"
#include "Coordinator.hpp"
#include "Transform.hpp"

class EntitySerializer : public XMLGenerator {
    public:
        /**
         * @brief Construct a new Entity Serializer object
         * 
         * @param filepath 
         */
        EntitySerializer(const std::string &filepath = "save.xml");
        /**
         * @brief Destroy the Entity Serializer object
         * 
         */
        ~EntitySerializer() = default;
        /**
         * @brief Construct a new Entity Serializer object
         * 
         * @param other 
         */
        EntitySerializer(const EntitySerializer& other) = default;
        /**
         * @brief Assignment operator
         * 
         * @param other 
         * @return EntitySerializer& 
         */
        EntitySerializer& operator=(const EntitySerializer& other) = default;

        // todo
        void SaveEntities();
        void SaveEntity(ECS::Entity& entity);
        void SerializeTransform(Component::Transform&);



    protected:
    private:
};

#endif /* !ENTITYSERIALIZER_HPP_ */
