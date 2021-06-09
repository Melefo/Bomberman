/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** EntityLoader
*/

#include "EntityLoader.hpp"

namespace Serialization
{
    // ! std::function is a mess
    std::map<std::string, void (*)(ECS::Entity&, boost::property_tree::ptree&)> EntityLoader::_loadAbleComponents = {
        std::pair<std::string, void (*)(ECS::Entity&, boost::property_tree::ptree&)>("Transform", &EntityLoader::LoadTransform),
        std::pair<std::string, void (*)(ECS::Entity&, boost::property_tree::ptree&)>("Renderer", &EntityLoader::LoadRenderer)
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
        boost::property_tree::ptree entityNode = ptree.get_child("Entity");

        for (auto it = _loadAbleComponents.begin(); it != _loadAbleComponents.end(); it++) {
            if (entityNode.find(it->first) != entityNode.not_found()) {
                it->second(entity, entityNode);
            }
        }
        return (entity);
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

}