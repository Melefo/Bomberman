/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Explosion
*/

#include "Explosion.hpp"
#include "Drawable3D.hpp"
#include <iostream>
#include "GameConfiguration.hpp"

namespace Component
{
    Explosion::Explosion(ECS::Entity& entity, ECS::Entity& parent, float radius, Explosion::ExplosionType startType, unsigned int startPower, float timer) :
    _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")), _myEntity(entity), _transform(_myEntity.GetComponent<Transform>()),
    _coordinator(ECS::Coordinator::GetInstance()), _parent(parent), _explosionSound(AssetCache::GetAsset<RayLib::Sound>("../assets/bomb/Bomb_sound_explosion.wav"))
    {
        _radius = radius;
        type = startType;
        power = startPower;
        _explosionTimer = timer;
    }

    void Explosion::Update(double, ECS::Entity&)
    {
        _explosionTimer -= _window->GetFrameTime();

        // ! draw wire sphere on the window to see/debug radius!
        if (Engine::GameConfiguration::GetDebugMode())
            _window->DrawSphereWires(_transform.position, _radius);

        CheckParentLeftRadius();

        if (_explosionTimer <= 0.0f) {
            Explode();
        }

    }

    void Explosion::Explode(void)
    {
        // ! chain bombs feature
        /*if (_explosionTimer > 0.05f) {
            for (auto childExplo : _childExplosions) {
                childExplo.get().Explode();
            }
        }*/

        _explosionSound->Play();

        RayLib::Circle areaOfEffect(_transform.position, _radius);
        std::vector<std::reference_wrapper<ECS::Entity>> entities = CollisionSystem::OverlapCircle(*_coordinator.get(), areaOfEffect);

        // ! j'ai pas trouvé mieux pour que la box soit récupérée
        for (auto it = entities.begin(); it != entities.end(); it++) {
            if (it->get().HasComponent<Destructible>()) {
                Destructible& destructible = it->get().GetComponent<Destructible>();
                destructible.TakeDamage(power);
            } else if (it->get().HasComponent<Box>()) {
                Box& destructible = it->get().GetComponent<Box>();
                destructible.TakeDamage(power);
            }

            // ? chain bombs feature

        }
        _myEntity.Dispose();
    }

    void Explosion::AddChildExplosion(Explosion& childExplo)
    {
        _childExplosions.push_back(childExplo);
    }

    void Explosion::CheckParentLeftRadius(void)
    {
        bool found = false;

        // si tu détruis ton parent, ne le cherche pas
        if (_explosionTimer <= 0.05f)
            return;

        // either already has a collider, or is not a center bomb
        if (_myEntity.OfType<Collider>().size() > 0 || !_myEntity.HasComponent<Drawable3D>())
            return;

        // happens if the factory creates a bomb
        if (_parent.GetId() == _myEntity.GetId())
            return;
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        Transform& transform = _myEntity.GetComponent<Transform>();

        RayLib::Circle checkZone(RayLib::Vector2<float>(transform.position), _radius);
        std::vector<std::reference_wrapper<ECS::Entity>> entities = CollisionSystem::OverlapCircle(*coordinator.get(), checkZone);
        for (auto entity = entities.begin(); entity != entities.end(); entity++) {
            if (entity->get().GetId() == _parent.GetId()) {
                found = true;
                //std::cout << "Parent is in radius " << _radius << std::endl;
            }
        }

        if (!found) {
            //std::cout << "Parent is no longer in radius " << _radius << std::endl;

            _myEntity.AddComponent<Collider, SquareCollider>(_myEntity,
                                                             std::vector<std::string>({"Player"}),
                                                             RayLib::Vector2<float>(transform.position.x, transform.position.z),
                                                             RayLib::Vector2<float>(transform.scale.x, transform.scale.z));
        }

    }

    void Explosion::FixedUpdate(ECS::Entity&)
    {

    }

    void Explosion::LateUpdate(double, ECS::Entity&)
    {

    }

    float Explosion::GetExplosionTimer() const
    {
        return (_explosionTimer);
    }
}