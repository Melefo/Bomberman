/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

namespace ECS
{
    Coordinator::Coordinator(std::string defaultScene, double fixedDeltaTime) :
    _systemManager(), _scenes(), _currentScene(defaultScene), _fixedDeltaTime(fixedDeltaTime), _duration(0), _firstRun(true)
    {
    }

    Entity& Coordinator::CreateEntity()
    {
        return this->_scenes[this->_currentScene].CreateEntity();
    }

    void Coordinator::Update(double dt)
    {
        for (auto &pair : this->_systemManager.GetSystems())
        {
            if (!pair.second->GetStatus())
                continue;
            auto dependencies = pair.second->GetDependencies();

            for (auto& entity : this->_scenes[this->_currentScene].GetEntities())
            {
                if (!entity->HasComponents(dependencies))
                    continue;
                pair.second->Update(dt, *entity);
            }
        }
    }

    void Coordinator::FixedUpdate()
    {
        for (auto& pair : this->_systemManager.GetSystems())
        {
            if (!pair.second->GetStatus())
                continue;
            auto dependencies = pair.second->GetDependencies();

            for (auto& entity : this->_scenes[this->_currentScene].GetEntities())
            {
                if (!entity->HasComponents(dependencies))
                    continue;
                pair.second->FixedUpdate(*entity);
            }
        }
    }

    void Coordinator::LateUpdate(double dt)
    {
        for (auto& pair : this->_systemManager.GetSystems())
        {
            if (!pair.second->GetStatus())
                continue;
            auto dependencies = pair.second->GetDependencies();

            for (auto& entity : this->_scenes[this->_currentScene].GetEntities())
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

    const std::vector<std::unique_ptr<Entity>>& Coordinator::GetEntities() const
    {
        return (this->_scenes.at(this->_currentScene).GetEntities());
    }

}