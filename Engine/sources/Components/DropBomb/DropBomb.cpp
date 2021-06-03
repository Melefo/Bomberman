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
    DropBomb::DropBomb(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator, int bombKey, float dropDelay)
    : _input(), _entity(attatchedEntity), _coordinator(coordinator), _transform(_entity.GetComponent<Transform>()),
      _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype"))
    {
        _bombKey = bombKey;
        _dropDelay = dropDelay;
        _timeToDrop = 0.0f;
        //_window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
    }

    void DropBomb::Update(double)
    {
        float windowFrameTime = _window->GetFrameTime();

        if (_timeToDrop > 0.0f) {
            _timeToDrop -= windowFrameTime;
        }

        if (_input.IsKeyDown(_bombKey) && _timeToDrop <= 0.0f) {
            InstantiateBomb(_transform.position, Explosion::ExplosionType::CIRCLE, 15.0f);
            std::cout << "Instantiate bomb" << std::endl;

            _timeToDrop = _dropDelay;
        }

    }

    void DropBomb::FixedUpdate(ECS::Entity& entity)
    {
        (void) entity;
    }

    void DropBomb::InstantiateBomb(RayLib::Vector3 position, Explosion::ExplosionType explosionType, float radius)
    {
        ECS::Entity& entity = _coordinator.CreateEntity();

        entity.AddComponent<Transform>(position, RayLib::Vector3(), RayLib::Vector3(10.0f, 10.0f, 10.0f));
        entity.AddComponent<Renderer>("../assets/bomb/bomb2.fbx", "../assets/bomb/bomb2_text.png");
        //! si on spawn une bombe sur le joueur, on est bloqués
        //entity.AddComponent<Collider, BoxCollider>(entity, _coordinator);
        entity.AddComponent<IBehaviour, Explosion>(entity, radius, explosionType);
    }

}
