/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Box
*/

#include "Box.hpp"
#include "EntityFactory.hpp"

namespace Component
{
    Box::Box(ECS::Entity& entity, int resistance, float lootChance) :
    Destructible(entity, resistance), _lootChance(lootChance)
    {
    }

    void Box::TakeDamage(int damage)
    {
        _resistance -= damage;

        if (_resistance <= 0) {
            _resistance = 0;
            if (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) <= _lootChance)
                SpawnLoot();
            _myEntity.Dispose();
        }
    }

    void Box::SpawnLoot(void)
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        // get camera
        Component::Camera& camera = Component::Camera::GetMainCamera();

        // create a factory
        EntityFactory factory(*coordinator.get(), camera.camera);
        // spawn a bonus
        ECS::Entity& pickup = factory.createPickUp();
        Transform& myTransform = _myEntity.GetComponent<Transform>();
        pickup.GetComponent<Transform>().position = myTransform.position;
    }

    std::ostream &Box::operator<<(std::ostream &os)
    {
        os << "<Box>";
        os << "<_resistance>" << _resistance << "</_resistance>";
        os << "<_lootChance>" << _lootChance << "</_lootChance>";
        os << "</Box>";
        return (os);
    }

    std::istream &Box::operator>>(std::istream &is)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::xml_parser::read_xml(is, tree);

        this->operator<<(tree);
        return (is);
    }

    boost::property_tree::ptree& Box::operator<<(boost::property_tree::ptree &ptree)
    {
        boost::property_tree::ptree node = ptree.get_child("Box");

        _resistance = node.get<int>("_resistance");
        _lootChance = node.get<float>("_lootChance");
        return (ptree);
    }
}
