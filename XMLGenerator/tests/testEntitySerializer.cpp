/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** testEntitySerializer
*/

#include "EntitySerializer.hpp"
#include <criterion/criterion.h>
#include "Coordinator.hpp"

Test(serializeEntity, transform)
{
    std::string filepath = "Entities.xml";
    EntitySerializer entitySerializer(filepath);
    std::string output;
    std::string desiredOutput =
        std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")+
        std::string("<Entity>\n")+
        std::string("\t<Transform>\n")+
        std::string("\t\t<position>\n")+
        std::string("\t\t\t<x>10</x>\n")+
        std::string("\t\t\t<y>0</y>\n")+
        std::string("\t\t\t<z>0</z>\n")+
        std::string("\t\t</position>\n")+
        std::string("\t\t<rotation>\n")+
        std::string("\t\t\t<x>0</x>\n")+
        std::string("\t\t\t<y>10</y>\n")+
        std::string("\t\t\t<z>0</z>\n")+
        std::string("\t\t</rotation>\n")+
        std::string("\t\t<scale>\n")+
        std::string("\t\t\t<x>0</x>\n")+
        std::string("\t\t\t<y>0</y>\n")+
        std::string("\t\t\t<z>10</z>\n")+
        std::string("\t\t</scale>\n")+
        std::string("\t</Transform>\n")+
        std::string("</Entity>\n");

    auto& coordinator = ECS::Coordinator::GetInstance();
    ECS::Entity& entity = coordinator->CreateEntity();

    entitySerializer.SaveEntities();

    entitySerializer.closeFile();

    entity.AddComponent<Component::Transform>(RayLib::Vector3(10.0f, 0.0f, 0.0f),
                                   RayLib::Vector3(0.0f, 10.0f, 0.0f),
                                   RayLib::Vector3(0.0f, 0.0f, 10.0f));

    std::ifstream stream(filepath);

    output = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    cr_expect_eq(output, desiredOutput);
    stream.close();
    //cr_assert_eq(remove(filepath.c_str()), 0);
}
