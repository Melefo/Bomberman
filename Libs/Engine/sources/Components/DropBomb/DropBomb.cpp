/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** DropBomb
*/

#include "DropBomb.hpp"
#include <iostream>
#include "Drawable3D.hpp"
#include "CollisionSystem.hpp"
#include "Camera.hpp"

namespace Component
{
    DropBomb::DropBomb(ECS::Entity& self, float delay, float minDelay, float maxBombs)
    : timeToDrop(0.0f), _coordinator(ECS::Coordinator::GetInstance()),
     _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")), _bombNumber(2), _defaultBombNumber(2),
     _bonusTime(0.0f), _defaultDropDelay(delay), _dropDelay(delay), _minDelay(minDelay), _maxBombs(maxBombs), _self(self)
    {
    }

    ECS::Entity& DropBomb::CreateBomb(ECS::Coordinator& coordinator, float radius, Explosion::ExplosionType type)
    {
        ECS::Entity& entity = coordinator.CreateEntity();
        entity.SetTag("Bomb");

        entity.AddComponent<Transform>(RayLib::Vector3(), RayLib::Vector3(-90, 0, 0), RayLib::Vector3(2, 2, 2));
        entity.AddComponent<IBehaviour, Explosion>(entity, _self, radius, type);
        return (entity);
    }

    void DropBomb::InstantiateBomb(RayLib::Vector3 position, Explosion::ExplosionType explosionType)
    {
        float explosionRadius = 2.50f;
        float boxSize = 7.50f;

        if (_bombNumber > _maxBombs)
            _bombNumber = static_cast<int>(_maxBombs);

        position = RayLib::Vector3(static_cast<float>(RoundToNearest10(position.x)), 0.0f, static_cast<float>(RoundToNearest10(position.z)));

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
        // ! for chainbomb feature
        // Explosion& firstExplo = firstBomb.GetComponent<Explosion>();
        firstBomb.GetComponent<Transform>().position = position;
        firstBomb.AddComponent<Component::Drawable3D>("../assets/bomb/Bomb_model.iqm", "../assets/bomb/Bomb_texture.png");

        bool reachedWall = false;

        for (auto dir = directions.begin(); dir != directions.end(); dir++) {
            reachedWall = false;
            for (float i = 0; i < _bombNumber; i++) {
                // if you encounter a wall, stop that direction

                RayLib::Vector3 wallCheckPos = position + (*dir) * i * boxSize;
                std::vector<std::reference_wrapper<ECS::Entity>> entitiesAtPosition = CollisionSystem::OverlapCircle(*coordinator.get(),
                                                                                                                     RayLib::Circle(RayLib::Vector2<float>(wallCheckPos.x, wallCheckPos.z),
                                                                                                                                    explosionRadius));

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

                // ! for chain bombs feature
                //firstExplo.AddChildExplosion(bomb.GetComponent<Explosion>());
            }
        }
    }

    int DropBomb::RoundToNearest10(float num)
    {
        float dec = num - std::floor(num);
        int rounded = static_cast<int>(std::floor(num));

        if (rounded % 10 < 5) {
            rounded = (rounded / 10) * 10;
        } else if(rounded % 10 ==5) {
            if(dec > 0)
                rounded = (((rounded + 10) / 10) * 10);
            else
                rounded = (rounded / 10) * 10;
        } else {
            rounded = (((rounded + 10) / 10) * 10);
        }
        return (rounded);
    }

    void DropBomb::Update()
    {
        float frameTime = RayLib::Window::GetInstance(0, "")->GetFrameTime();

        if (_dropDelay < _minDelay)
            _dropDelay = _minDelay;

        if (_bonusTime > 0.0f) {
            _bonusTime -= frameTime;
        } else {
            if (_bombNumber != _defaultBombNumber) {
                _bombNumber = _defaultBombNumber;
            }
            if (_dropDelay != _defaultDropDelay) {
                _dropDelay = _defaultDropDelay;
            }
        }
    }

    float DropBomb::GetDropDelay(void)
    {
        return (_dropDelay);
    }

    int DropBomb::GetBombNumber()
    {
        return (_bombNumber);
    }

    void DropBomb::BoostBombNumber(int bonusBombs, float duration)
    {
        _bombNumber = bonusBombs;
        _bonusTime = duration;
    }

    void DropBomb::BoostBombCooldown(float bonusDelay, float duration)
    {
        _dropDelay = bonusDelay;
        _bonusTime = duration;
    }
}
