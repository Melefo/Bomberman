/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** DropBomb
*/

#include "DropBomb.hpp"
#include <iostream>

namespace Component
{
    DropBomb::DropBomb(float delay)
    : _coordinator(ECS::Coordinator::GetInstance()),
     _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype"))
    {
        dropDelay = dropDelay;
        timeToDrop = 0.0f;
    }

    void DropBomb::InstantiateBomb(RayLib::Vector3 position, Explosion::ExplosionType explosionType, float radius)
    {
        ECS::Entity& entity = _coordinator->CreateEntity();

        entity.AddComponent<Transform>(position, RayLib::Vector3(), RayLib::Vector3(10.0f, 10.0f, 10.0f));
        entity.AddComponent<Renderer>("../assets/bomb/bomb2.fbx", "../assets/bomb/bomb2_text.png");
        std::cout << "Helo" << std::endl;
        //! si on spawn une bombe sur le joueur, on est bloqués
        //entity.AddComponent<Collider, BoxCollider>(entity, _coordinator);
        entity.AddComponent<IBehaviour, Explosion>(entity, radius, explosionType);
    }

}
