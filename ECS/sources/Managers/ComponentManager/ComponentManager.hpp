/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Exceptions.hpp"
#include "IComponent.hpp"

namespace ECS
{
    class ComponentManager
    {
        private:
            std::unordered_map<std::string, std::vector<std::string>> _bases;
            std::unordered_map<std::string, std::unique_ptr<IComponent>> _components;
        public:
            ComponentManager();
            ~ComponentManager() = default;

            template<typename T>
            T &GetComponent()
            {
                std::string name(typeid(T).name());

                const auto &it = this->_components.find(name);
                if (it == this->_components.end())
                    throw Exception::EntityException("Entity doesn't contains this Component");
                return dynamic_cast<T &>(*it->second);
            }
            template<typename T>
            std::vector<std::reference_wrapper<T>> OfType()
            {
                std::string baseName(typeid(T).name());
                std::vector<std::reference_wrapper<T>> list;
                const auto &it = this->_bases.find(baseName);

                if (it == this->_bases.end())
                    return list;
                for (std::string& name : it->second)
                    list.push_back(dynamic_cast<T&>(*this->_components[name]));
                return list;
            }
            template<typename T, typename... TArgs>
            void AddComponent(TArgs&&... args)
            {
                std::string name(typeid(T).name());

                if (this->HasComponent<T>())
                    throw Exception::EntityException("Entity already contains this Component");
                this->_components[name] = std::make_unique<T>(std::forward<TArgs>(args)...);
            }
            template<typename Base, typename T, typename... TArgs>
            void AddComponent(TArgs&&... args)
            {
                static_assert(std::is_base_of<Base, T>::value, "Class doesn't inherit from Base");
                std::string name(typeid(T).name());

                if (this->HasComponent<T>())
                    throw Exception::EntityException("Entity already contains this Component");
                this->_components[name] = std::make_unique<T>(std::forward<TArgs>(args)...);

                std::string baseName(typeid(Base).name());

                if (this->_bases.find(baseName) == this->_bases.end())
                    this->_bases[baseName] = std::vector<std::string>();
                this->_bases[baseName].push_back(name);
            }
            template<typename T>
            void RemoveComponent()
            {
                std::string name(typeid(T).name());

                const auto &it = this->_components.find(name);

                if (it == this->_components.end())
                    return;
                for (auto &base : this->_bases)
                {
                    const auto &found = std::find(base.second.begin(), base.second.end(), it->first);
                    if (found != base.second.end())
                        base.second.erase(found);
                    if (base.second.size() == 0)
                        this->_bases.erase(base.first);
                }
                this->_components.erase(it);
            }
            template<typename T>
            bool HasComponent() const
            {
                for (auto &pair : this->_components)
                {
                    IComponent &component = *pair.second;

                    try
                    {
                        dynamic_cast<T &>(component);
                        return true;
                    }
                    catch (std::bad_cast &exp)
                    {
                    }
                }
                return false;
            }
            bool HasComponent(std::string &name) const;
            bool HasComponents(std::vector<std::string> &names) const;
    };
}

#endif /* !COMPONENTMANAGER_HPP_ */
