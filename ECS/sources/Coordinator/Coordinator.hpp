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
    /**
     * @brief Public class used to manipulates scenes and theirs entities and systems.
     * 
     */
    class Coordinator
    {
        private:
            /**
             * @brief Coordinator singleton
             * 
             */
            static std::unique_ptr<Coordinator> _coordinator;

            /**
             * @brief Where all systems are stores
             * 
             */
            SystemManager _systemManager;
            /**
             * @brief List of scenes to store theirs entities
             * 
             */
            std::map<std::string, EntityManager> _scenes;
            /**
             * @brief Name of the current loaded scene
             * 
             */
            std::string _currentScene;

            /**
             * @brief Time between each call of FixedUpdate
             * 
             */
            double _fixedDeltaTime;
            /**
             * @brief Total of time since the last call of FixedUpdate
             * 
             */
            double _duration;
            /**
             * @brief Time of last call of Run
             * 
             */
            std::chrono::high_resolution_clock::time_point _lastRun;
            /**
             * @brief Check if Run has been call at least one time
             * 
             */
            bool _firstRun;

            /**
             * @brief Update all entities from the current scene with the actived systems
             * 
             * @param dt The inverval in seconds from the last update
             */
            void Update(double dt);
            /**
             * @brief Update all entities from the current scene with the actived systems at a specific time
             * 
             */
            void FixedUpdate();
            /**
             * @brief Update all entities from the current scene after the call of Update
             * 
             * @param dt The inverval in seconds from the last update
             */
            void LateUpdate(double dt);
        public:
            /**
             * @brief Construct a new Coordinator object
             * 
             * @param defaultScene Name of the default scene loaded
             * @param fixedDeltaTime Time between each call of FixedUpdate
             */
            Coordinator(std::string defaultScene = "MainMenu", double fixedDeltaTime = 0.02);
            /**
             * @brief Destroy the Coordinator object
             * 
             */
            ~Coordinator() = default;
            /**
             * @brief Copy a new Coordinator object
             * 
             */
            Coordinator(const Coordinator&) = delete;
            /**
             * @brief Assign a new Coordinator object
             * 
             * @return Coordinator& assigned Coordinator
             */
            Coordinator& operator=(const Coordinator&) = delete;

            /**
             * @brief Add a system to update entities
             * 
             * @tparam T Type of the system to add
             * @tparam TArgs Types of constructor arguments of T
             * @param args Constructor arguments
             * @return T& Newly added System
             */
            template<typename T, typename... TArgs>
            T& AddSystem(TArgs&&... args)
            {
                return this->_systemManager.AddSystem<T>(std::forward<TArgs>(args)...);
            }
            /**
             * @brief Create a Entity object
             * 
             * @return Entity& newly create entity inside current scene
             */
            Entity &CreateEntity();
            /**
             * @brief Remove a system from the list which updates entities
             * 
             * @tparam T Type of the system to remove
             */
            template<typename T>
            void RemoveSystem()
            {
                this->_systemManager.RemoveSystem<T>();
            }
            /**
             * @brief Execute FixedUpdate, Update & LateUpdate
             * 
             */
            void Run();
            /**
             * @brief Get the Fixed Delta Time object
             * 
             * @return double current time in seconds between each call of FixedUpdate
             */
            double getFixedDeltaTime() const;
            /**
             * @brief Get a unique_ptr to the coordinator Singleton
             * 
             * @param defaultScene 
             * @param fixedDeltaTime 
             * @return std::unique_ptr<Coordinator>& 
             */
            static std::unique_ptr<Coordinator>& GetInstance(std::string defaultScene = "MainMenu", double fixedDeltaTime = 0.02);

            /**
             * @brief Get a list of the entities in the current scene
             * 
             * @return const std::list<std::unique_ptr<Entity>>& 
             */
            const std::list<std::unique_ptr<Entity>>& GetEntities();

            /**
             * @brief Get the Current Scene object
             * 
             * @return const std::string& 
             */
            const std::string &getCurrentScene(void);

            /**
             * @brief Set the Current Scene object
             * 
             * @param sceneName 
             */
            void setCurrentScene(std::string &sceneName);

            /**
             * @brief Get a Scene object from a name
             * 
             * @param sceneName 
             * @return ECS::EntityManager& 
             */
            const ECS::EntityManager &getScene(std::string &sceneName) const;

            /**
             * @brief Close Window
             * 
             */
            bool CloseWindow;
    };
}

#endif /* !COORDINATOR_HPP_ */
