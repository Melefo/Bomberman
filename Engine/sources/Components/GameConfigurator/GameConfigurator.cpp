/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfigurator
*/

#include "GameConfigurator.hpp"

namespace Component
{

    void GameConfigurator::Update(double, ECS::Entity&)
    {
        int count = 0;
        std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(), "");

        // if drag n drop
        if (window->IsFileDropped())
        {
            std::vector<std::string> droppedFiles = window->GetDroppedFiles(&count);
            // open file
            std::cout << droppedFiles[0] << std::endl;

            Serialization::EntityLoader::LoadEntity(droppedFiles[0]);
        }
    }

    void GameConfigurator::FixedUpdate(ECS::Entity&)
    {

    }

    void GameConfigurator::LateUpdate(double, ECS::Entity&)
    {

    }
}
