/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

namespace ECS
{
    std::unique_ptr<Coordinator> Coordinator::_coordinator = nullptr;


    Coordinator::Coordinator(std::string defaultScene, double fixedDeltaTime) :
    _systemManager(), _scenes(), _currentScene(defaultScene), _fixedDeltaTime(fixedDeltaTime), _duration(0), _firstRun(true), CloseWindow(false)
    {

    }

    std::unique_ptr<Coordinator>& Coordinator::GetInstance(std::string defaultScene, double fixedDeltaTime)
    {
        if (_coordinator == nullptr) {
            _coordinator = std::make_unique<Coordinator>(defaultScene, fixedDeltaTime);
        }
        return (_coordinator);
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

            auto& entities = this->_scenes[this->_currentScene].GetEntities();
            for (auto it = entities.begin(); it != entities.end();) {

                auto entity = it->get();
                it++;
                if (entity->HasComponents(dependencies)) {
                    pair.second->Update(dt, *entity);
                }
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

            auto& entities = this->_scenes[this->_currentScene].GetEntities();
            for (auto it = entities.begin(); it != entities.end();) {

                auto entity = it->get();
                it++;
                if (entity->HasComponents(dependencies)) {
                    pair.second->FixedUpdate(*entity);
                }
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

            auto& entities = this->_scenes[this->_currentScene].GetEntities();
            for (auto it = entities.begin(); it != entities.end();) {

                auto entity = it->get();
                it++;
                if (entity->HasComponents(dependencies)) {
                    pair.second->LateUpdate(dt, *entity);
                }
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

    const std::list<std::unique_ptr<Entity>>& Coordinator::GetEntities()
    {
        return this->_scenes[this->_currentScene].GetEntities();
    }

    const std::string &Coordinator::getCurrentScene(void)
    {
        return (_currentScene);
    }

}