/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** EntityLoader
*/

#include "EntityLoader.hpp"
#include "EngineExceptions.hpp"
#include "PhysicsBody.hpp"
#include "Collider.hpp"
#include "SquareCollider.hpp"

namespace Serialization
{
    std::map<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>> EntityLoader::_loadAbleComponents = {
        std::pair<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>>("Transform", &EntityLoader::LoadTransform),
        std::pair<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>>("Destructible", &EntityLoader::LoadDestructible),
        std::pair<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>>("Box", &EntityLoader::LoadBox),
        std::pair<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>>("PhysicsBody", &EntityLoader::LoadPhysicsBody),
        std::pair<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>>("SquareCollider", &EntityLoader::LoadSquareCollider)
    };

    ECS::Entity& EntityLoader::LoadEntity(std::istream& iss)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::xml_parser::read_xml(iss, tree);

        return (LoadEntity(tree));
    }

    ECS::Entity& EntityLoader::LoadEntity(boost::property_tree::ptree &ptree)
    {
        // ! check the ptree contains entity
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        ECS::Entity& entity = coordinator->CreateEntity();
        //boost::property_tree::ptree entityNode = ptree.get_child("Entity");

        entity.SetTag(ptree.get<std::string>("tag"));

        entity.AddComponent<Component::Transform>();

        for (auto it = _loadAbleComponents.begin(); it != _loadAbleComponents.end(); it++) {
            if (ptree.find(it->first) != ptree.not_found()) {
                it->second(entity, ptree);
            }
        }
        std::cout << "Created entity with tag: " << entity.GetTag() << std::endl;

        return (entity);
    }

    void EntityLoader::LoadEntities(std::istream& iss)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::xml_parser::read_xml(iss, tree);

        LoadEntities(tree);
    }

    void EntityLoader::LoadEntities(boost::property_tree::ptree &ptree)
    {
        if (ptree.find("Entities") == ptree.not_found())
            throw Engine::Exception::EngineException("Entity node not found in XML");

        boost::property_tree::ptree entitiesNode = ptree.get_child("Entities");

        if (entitiesNode.find("Entity") == entitiesNode.not_found())
            throw Engine::Exception::EngineException("Entity node not found in XML");

        for (auto& it : entitiesNode) {
            boost::property_tree::ptree entityNode = it.second;
            LoadEntity(entityNode);
        }
    }

    void EntityLoader::LoadTransform(ECS::Entity& entity, boost::property_tree::ptree &ptree)
    {
        if (!entity.HasComponent<Component::Transform>())
            entity.AddComponent<Component::Transform>();
        entity.GetComponent<Component::Transform>() << ptree;
    }

    void EntityLoader::LoadDestructible(ECS::Entity& entity, boost::property_tree::ptree &ptree)
    {
        entity.AddComponent<Component::Destructible>(entity);
        entity.GetComponent<Component::Destructible>() << ptree;
    }

    void EntityLoader::LoadBox(ECS::Entity& entity, boost::property_tree::ptree &ptree)
    {
        entity.AddComponent<Component::Box>(entity);
        entity.GetComponent<Component::Box>() << ptree;
    }

    void EntityLoader::LoadPhysicsBody(ECS::Entity& entity, boost::property_tree::ptree&)
    {
        entity.AddComponent<Component::PhysicsBody>();
    }

    void EntityLoader::LoadSquareCollider(ECS::Entity& entity, boost::property_tree::ptree &ptree)
    {
        entity.AddComponent<Component::Collider, Component::SquareCollider>(entity, std::vector<std::string>({}), 0.0f, 0.0f);
        entity.OfType<Component::Collider>()[0].get() << ptree;
    }
}