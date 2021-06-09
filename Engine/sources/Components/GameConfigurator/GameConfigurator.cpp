/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfigurator
*/

#include "GameConfigurator.hpp"

namespace Component
{

    GameConfigurator::GameConfigurator() : _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(), ""))
    {

    }


    void GameConfigurator::Update(double, ECS::Entity&)
    {
        int count = 0;
        // dans le constructeur

        // if drag n drop
        if (_window->IsFileDropped())
        {
            std::vector<std::string> droppedFiles = _window->GetDroppedFiles(&count);
            // open file
            std::ifstream myfile(droppedFiles[0]);

            std::stringstream buffer;
            buffer << myfile.rdbuf();

            std::istringstream iss;
            iss.str(buffer.str());
            myfile.close();

            //std::cout << iss.str() << std::endl;
            std::cout << "Dropped file: " << droppedFiles[0] << std::endl;

            Serialization::EntityLoader::LoadEntity(iss);
            _window->ClearDroppedFiles();
        }

    }

    void GameConfigurator::FixedUpdate(ECS::Entity&)
    {

    }

    void GameConfigurator::LateUpdate(double, ECS::Entity&)
    {

    }
}
