/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** EntityLoader
*/

#include "EntityLoader.hpp"

namespace Serialization
{
    std::map<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>> EntityLoader::_loadAbleComponents = {
        std::pair<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>>("Transform", &EntityLoader::LoadTransform),
        std::pair<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>>("Renderer", &EntityLoader::LoadRenderer),
        std::pair<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>>("BoxCollider", &EntityLoader::LoadBoxCollider),
        std::pair<std::string, std::function<void(ECS::Entity&, boost::property_tree::ptree&)>>("Destructible", &EntityLoader::LoadDestructible)
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

        for (auto it = _loadAbleComponents.begin(); it != _loadAbleComponents.end(); it++) {
            if (ptree.find(it->first) != ptree.not_found()) {
                it->second(entity, ptree);
            }
        }
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
        boost::property_tree::ptree entitiesNode = ptree.get_child("Entities");

        for (auto& it : entitiesNode) {
            boost::property_tree::ptree entityNode = it.second;
            LoadEntity(entityNode);
        }
    }

    void EntityLoader::LoadTransform(ECS::Entity& entity, boost::property_tree::ptree &ptree)
    {
        entity.AddComponent<Component::Transform>();
        entity.GetComponent<Component::Transform>() << ptree;
    }

    void EntityLoader::LoadRenderer(ECS::Entity& entity, boost::property_tree::ptree &ptree)
    {
        entity.AddComponent<Component::Renderer>();
        entity.GetComponent<Component::Renderer>() << ptree;
    }

    void EntityLoader::LoadBoxCollider(ECS::Entity& entity, boost::property_tree::ptree& ptree)
    {
        //! ne fonctionne uniquement si Transform précede BoxCollider
        //! à cause du unordered map, c'est aléatoire, donc le box collider ne trouve pas son transform, et crash
        entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, 1.0f);
        std::vector<std::reference_wrapper<Component::Collider>> cols = entity.OfType<Component::Collider>();

        for (auto col = cols.begin(); col != cols.end(); col++) {
            col->get() << ptree;
        }
    }

    void EntityLoader::LoadDestructible(ECS::Entity& entity, boost::property_tree::ptree &ptree)
    {
        entity.AddComponent<Component::Destructible>(entity);
        entity.GetComponent<Component::Destructible>() << ptree;
    }

}