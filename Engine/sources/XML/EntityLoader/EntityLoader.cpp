/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** EntityLoader
*/

#include "EntityLoader.hpp"

namespace Serialization
{
    ECS::Entity& EntityLoader::LoadEntity(std::istream& iss)
    {
        // get the coordinator
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        // create an entity
        ECS::Entity& entity = coordinator->CreateEntity();

        boost::property_tree::ptree tree;
        boost::property_tree::xml_parser::read_xml(iss, tree);

        // get the ptree <Entity>
        boost::property_tree::ptree entityNode = tree.get_child("Entity");

        // ! une meilleure solution ? Laisser boost nous donner l'erreur ?
        // ! foreach : child node -> create IComponent et on l'ajoute ?
        entity.AddComponent<Component::Transform>();
        entity.GetComponent<Component::Transform>() << entityNode;

        entity.AddComponent<Component::Renderer>();
        entity.GetComponent<Component::Renderer>() << entityNode;
        return (entity);
    }

    ECS::Entity& EntityLoader::LoadEntity(boost::property_tree::ptree &ptree)
    {
        // get the coordinator
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        // create an entity
        ECS::Entity& entity = coordinator->CreateEntity();

        // get the ptree <Entity>
        boost::property_tree::ptree entityNode = ptree.get_child("Entity");

        // ! une meilleure solution ? Laisser boost nous donner l'erreur ?
        if (ptree.find("Transform") != ptree.not_found()) {
            entity.AddComponent<Component::Transform>();
            entity.GetComponent<Component::Transform>() << entityNode;
        }
        if (ptree.find("Renderer") != ptree.not_found()) {
            entity.AddComponent<Component::Renderer>();
            entity.GetComponent<Component::Renderer>() << entityNode;
        }
        return (entity);
    }
}