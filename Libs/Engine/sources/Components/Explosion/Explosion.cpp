/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Explosion
*/

#include "Explosion.hpp"
#include "Drawable3D.hpp"
#include <iostream>
#include "EntityFactory.hpp"
#include "GameConfiguration.hpp"

namespace Component
{
    Explosion::Explosion(ECS::Entity& entity, ECS::Entity& parent, float radius, Explosion::ExplosionType startType, unsigned int startPower, float timer) :
    _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")), _myEntity(entity), _transform(_myEntity.GetComponent<Transform>()),
    _coordinator(ECS::Coordinator::GetInstance()), _parent(parent), _explosionSound(AssetCache::GetAsset<RayLib::Sound>("../assets/bomb/Bomb_sound_explosion.wav")),
    _exploding(false)
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
        //! évite les boucles inf de bombes qui s'entre-explosent
        if (_exploding)
            return;

        _exploding = true;

        // ! chain bombs feature
        if (_explosionTimer > 0.05f) {
            for (auto childExplo : _childExplosions) {
                childExplo.get().Explode();
            }
        }

        _explosionSound->Play();

        RayLib::Circle areaOfEffect(_transform.position, _radius);
        std::vector<std::reference_wrapper<ECS::Entity>> entities = CollisionSystem::OverlapCircle(*_coordinator.get(), areaOfEffect);

        // ! j'ai pas trouvé mieux pour que la box soit récupérée
        for (auto it = entities.begin(); it != entities.end();) {

            auto& entity = it->get();
            it++;

            if (entity.HasComponent<Destructible>()) {
                Destructible& destructible = entity.GetComponent<Destructible>();
                destructible.TakeDamage(power);
                continue;
            } else if (entity.HasComponent<Box>()) {
                Box& destructible = entity.GetComponent<Box>();
                destructible.TakeDamage(power);
                continue;
            }

            if (entity.HasComponent<Explosion>() && entity.GetId() != _myEntity.GetId()) {
                entity.GetComponent<Explosion>().Explode();
                continue;
            }
        }

        SpawnParticles();

        _myEntity.Dispose();
    }

    void Explosion::SpawnParticles(void)
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

        // create a factory
        EntityFactory factory(*coordinator.get());

        for (int i = 0; i < 10; i++) {
            ECS::Entity& particle = factory.createParticle("../assets/bomb/Bomb_texture.png",
                                                           RayLib::Vector2<float>(1.0f, 1.5f),
                                                           RayLib::Vector2<int>(4, 5), 4.0f, 0.5f);
            Transform& myTransform = _myEntity.GetComponent<Transform>();
            particle.GetComponent<Transform>().position = myTransform.position;
        }
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