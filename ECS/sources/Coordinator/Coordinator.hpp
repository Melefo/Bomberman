/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Coordinator
*/

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

#include <chrono>
#include <memory>
#include <string>
#include <map>
#include "SystemManager.hpp"
#include "EntityManager.hpp"

namespace ECS
{
    class Coordinator
    {
        private:
            SystemManager _systemManager;
            std::map<std::string, EntityManager> _scenes;
            std::string _currentScene;

            double _fixedDeltaTime;
            double _duration;
            std::chrono::high_resolution_clock::time_point _lastRun;
            bool _firstRun;

            void Update(double dt);
            void FixedUpdate();
            void LateUpdate(double dt);
        public:
            Coordinator(std::string defaultScene = "MainMenu", double fixedDeltaTime = 0.02);
            ~Coordinator() = default;
    
            template<typename T, typename... TArgs>
            T &AddSystem(TArgs&&... args)
            {
                return this->_systemManager.AddSystem<T>(std::forward<TArgs>(args)...);
            }
            Entity &CreateEntity();
            template<typename T>
            void RemoveSystem()
            {
                this->_systemManager.RemoveSystem<T>();
            }
            void Run();
            double getFixedDeltaTime() const;
    };
}

#endif /* !COORDINATOR_HPP_ */
