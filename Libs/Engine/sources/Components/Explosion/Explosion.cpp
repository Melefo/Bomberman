/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Explosion
*/

#include "Explosion.hpp"
#include <iostream>

namespace Component
{
    Explosion::Explosion(ECS::Entity& entity, float radius, Explosion::ExplosionType startType, unsigned int startPower, float timer) :
    _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")), _myEntity(entity), _transform(_myEntity.GetComponent<Transform>()),
    _coordinator(ECS::Coordinator::GetInstance())
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
    }

    void Explosion::FixedUpdate(ECS::Entity&)
    {

    }

    void Explosion::LateUpdate(double, ECS::Entity&)
    {

    }
}