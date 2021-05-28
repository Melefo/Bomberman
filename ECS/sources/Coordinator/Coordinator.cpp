/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

namespace ECS
{
    Coordinator::Coordinator(double fixedDeltaTime) :
    _systemManager(), _entityManager(), _fixedDeltaTime(fixedDeltaTime), _duration(0), _firstRun(true)
    {
    }

    Entity &Coordinator::CreateEntity()
    {
        return this->_entityManager.CreateEntity();
    }

    void Coordinator::DeleteEntity(Entity &entity)
    {
        this->_entityManager.DeleteEntity(entity);
    }

    void Coordinator::Update(double dt)
    {
        for (auto &pair : this->_systemManager.GetSystems())
        {
            if (!pair.second->GetStatus())
                continue;
            auto dependencies = pair.second->GetDependencies();

            for (auto &entity : this->_entityManager.GetEntities())
            {
                if (!entity->HasComponents(dependencies))
                    continue;
                pair.second->Update(dt, *entity);
            }
        }
    }

    void Coordinator::FixedUpdate()
    {
        for (auto &pair : this->_systemManager.GetSystems())
        {
            if (!pair.second->GetStatus())
                continue;
            auto dependencies = pair.second->GetDependencies();

            for (auto &entity : this->_entityManager.GetEntities())
            {
                if (!entity->HasComponents(dependencies))
                    continue;
                pair.second->FixedUpdate(*entity);
            }
        }
    }

    void Coordinator::LateUpdate(double dt)
    {
        for (auto &pair : this->_systemManager.GetSystems())
        {
            if (!pair.second->GetStatus())
                continue;
            auto dependencies = pair.second->GetDependencies();

            for (auto &entity : this->_entityManager.GetEntities())
            {
                if (!entity->HasComponents(dependencies))
                    continue;
                pair.second->LateUpdate(dt, *entity);
            }
        }
    }

    void Coordinator::Run()
    {
        double dt = 0;
        auto now = std::chrono::high_resolution_clock::now();

        if (this->_firstRun)
            this->_firstRun = false;
        else
            dt = std::chrono::duration<double, std::chrono::seconds::period>(now - this->_lastRun).count();
        this->_duration += dt;

        if (this->_duration > this->_fixedDeltaTime) {
            this->_duration -= this->_fixedDeltaTime;
            this->FixedUpdate();
        }
        this->Update(dt);
        this->LateUpdate(dt);

        this->_lastRun = now;
    }

    double Coordinator::getFixedDeltaTime() const
    {
        return this->_fixedDeltaTime;
    }
}