/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Coordinator
*/

#include <chrono>
#include "Coordinator.hpp"

#include <iostream>

namespace ECS
{
    Entity &Coordinator::CreateEntity()
    {
        return this->_entityManager.CreateEntity();
    }

    void Coordinator::DeleteEntity(Entity &entity)
    {
        this->_entityManager.DeleteEntity(entity);
    }

    void Coordinator::Update()
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (auto &pair : this->_systemManager.GetSystems())
        {
            auto dependencies = pair.second->GetDependencies();

            for (auto &entity : this->_entityManager.GetEntities())
            {
                if (!entity->HasComponents(dependencies))
                    continue;
                pair.second->Update(this->_dt, *entity);
            }
        }

        auto stop = std::chrono::high_resolution_clock::now();
		this->_dt = std::chrono::duration<double, std::chrono::seconds::period>(stop - start).count();
    }
}