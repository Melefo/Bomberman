/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Explosion
*/

#include "Explosion.hpp"
#include <iostream>
#include "GameConfiguration.hpp"

namespace Component
{
    Explosion::Explosion(ECS::Entity& entity, ECS::Entity& parent, float radius, Explosion::ExplosionType startType, unsigned int startPower, float timer) :
    _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")), _myEntity(entity), _transform(_myEntity.GetComponent<Transform>()),
    _coordinator(ECS::Coordinator::GetInstance()), _parent(parent)
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

        if (_explosionTimer <= 0.0f) {
            std::cout << "BOOM" << std::endl;
            // get the assetmanager
            std::unique_ptr<AssetManager> &assetManagerRef = AssetManager::GetInstance();
            // get the sounds
            std::map<std::string, RayLib::Sound>& sounds = assetManagerRef->getAssetFromName("Bomb").getSounds();
            // play sound explosion
            if (sounds.find("explosion") != sounds.end()) {
                sounds.find("explosion")->second.Play();
            }

            std::vector<std::reference_wrapper<ECS::Entity>> entities = CollisionSystem::OverlapSphere(*_coordinator.get(), _transform.position, _radius);

            // ! j'ai pas trouvé mieux pour que la box soit récupérée
            for (auto it = entities.begin(); it != entities.end(); it++) {
                if (it->get().HasComponent<Destructible>()) {
                    Destructible& destructible = it->get().GetComponent<Destructible>();
                    destructible.TakeDamage(power);
                } else if (it->get().HasComponent<Box>()) {
                    Box& destructible = it->get().GetComponent<Box>();
                    destructible.TakeDamage(power);
                }
            }
            _myEntity.Dispose();
        }

        CheckParentLeftRadius();
    }

    void Explosion::CheckParentLeftRadius(void)
    {
        bool found = false;

        // si tu détruis ton parent, ne le cherche pas
        if (_explosionTimer <= 0.05f)
            return;

        // either already has a collider, or is not a center bomb
        if (_myEntity.OfType<Collider>().size() > 0 || !_myEntity.HasComponent<Renderer>())
            return;

        // happens if the factory creates a bomb
        if (_parent.GetId() == _myEntity.GetId())
            return;
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        Transform& transform = _myEntity.GetComponent<Transform>();

        std::vector<std::reference_wrapper<ECS::Entity>> entities = CollisionSystem::OverlapSphere(*coordinator.get(), transform.position, _radius);
        for (auto entity = entities.begin(); entity != entities.end(); entity++) {
            if (entity->get().GetId() == _parent.GetId()) {
                found = true;
                std::cout << "Parent is in radius " << _radius << std::endl;

            }
        }

        if (!found) {
            std::cout << "Parent is no longer in radius " << _radius << std::endl;

            _myEntity.AddComponent<Collider, SphereCollider>(_myEntity, transform.position, _radius);
        }

    }

    void Explosion::FixedUpdate(ECS::Entity&)
    {

    }

    void Explosion::LateUpdate(double, ECS::Entity&)
    {

    }
}