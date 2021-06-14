/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** StorageComponent
*/

#ifndef STORAGECOMPONENT_HPP_
#define STORAGECOMPONENT_HPP_

#include "IComponent.hpp"

class StorageComponent : public ECS::IComponent
{
    public:
        StorageComponent() = delete;
        StorageComponent(int start) : value(start) {}
        ~StorageComponent() override = default;
        int value;

        std::ostream &operator<<(std::ostream &os) override {return os;};
        std::istream &operator>>(std::istream &is) override {return is;};
        boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

};

#endif /* !STORAGECOMPONENT_HPP_ */
