/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** DropBomb
*/

#include "DropBomb.hpp"
#include <iostream>
#include "CollisionSystem.hpp"
#include "Camera.hpp"

namespace Component
{
    DropBomb::DropBomb(float delay)
    : dropDelay(delay), timeToDrop(0.0f), _coordinator(ECS::Coordinator::GetInstance()),
     _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype"))
    {
    }

    ECS::Entity& DropBomb::CreateBomb(ECS::Coordinator& coordinator, float radius, Explosion::ExplosionType type)
    {
        ECS::Entity& entity = coordinator.CreateEntity();
        entity.SetTag("Bomb");

        entity.AddComponent<Transform>(RayLib::Vector3(), RayLib::Vector3(), RayLib::Vector3(10.0f, 10.0f, 10.0f));
        entity.AddComponent<Renderer>("Bomb");
        //! si on spawn une bombe sur le joueur, on est bloqués
        //entity.AddComponent<Collider, BoxCollider>(entity, _coordinator);
        entity.AddComponent<IBehaviour, Explosion>(entity, radius, type);
        return (entity);
    }


    void DropBomb::InstantiateBomb(RayLib::Vector3 position, Explosion::ExplosionType explosionType, float radius)
    {
        float explosionRadius = 2.50f;
        float boxSize = 7.50f;

        // spawn a bunch of small bombs in a cross pattern of size radius
        // create a bunch of directions vectors
        std::vector<RayLib::Vector3> directions = {RayLib::Vector3(1.0f, 0.0f, 0.0f),
                                                   RayLib::Vector3(0.0f, 0.0f, 1.0f),
                                                   RayLib::Vector3(-1.0f, 0.0f, 0.0f),
                                                   RayLib::Vector3(0.0f, 0.0f, -1.0f)};

        // loop over them + radius
        // create entity factory and create bombs
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

        // create a bomb at position
        ECS::Entity& firstBomb = CreateBomb(*coordinator.get(), explosionRadius, explosionType);
        firstBomb.GetComponent<Transform>().position = position;

        bool reachedWall = false;

        for (auto dir = directions.begin(); dir != directions.end(); dir++) {
            reachedWall = false;
            for (float i = 0; i < radius; i++) {
                // if you encounter a wall, stop that direction
                std::vector<std::reference_wrapper<ECS::Entity>> entitiesAtPosition = CollisionSystem::OverlapSphere(*coordinator.get(), position + 
                (*dir) * i * boxSize, explosionRadius);

                for (auto entity = entitiesAtPosition.begin(); entity != entitiesAtPosition.end(); entity++) {
                    if (entity->get().GetTag() == "Wall") {
                        std::cout << "Stopped cross" << std::endl;
                        reachedWall = true;
                    }
                }
                if (reachedWall) {
                    break;
                }

                // create small bombs of radius boxsize
                ECS::Entity& bomb = CreateBomb(*coordinator.get(), explosionRadius, explosionType);

                // spacing = boxsize so radius * boxsize
                bomb.GetComponent<Transform>().position = position + (*dir) * i * boxSize;
            }
        }
    }

}
