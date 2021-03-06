/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** APickUp
*/

#include "APickUp.hpp"

namespace Component
{
    APickUp::APickUp(ECS::Entity& entity, float pickupRadius)
    : _entity(entity), _pickupRadius(pickupRadius), _coordinator(*ECS::Coordinator::GetInstance())
    {
    }

    void APickUp::FixedUpdate(ECS::Entity& entity)
    {
        if (entity.HasComponent<Transform>()) {
            Transform& transform = entity.GetComponent<Transform>();
            std::vector<std::reference_wrapper<ECS::Entity>> entities = CollisionSystem::OverlapCircle(_coordinator, RayLib::Circle(RayLib::Vector2<float>(transform.position.x, transform.position.z),
                                                                                                                                    _pickupRadius));
            for (auto it = entities.begin(); it != entities.end(); it++) {
                if (it->get().GetTag().find("PlayerEntity") != std::string::npos || it->get().GetTag().find("AI") != std::string::npos) {
                    OnPickup(it->get());
                }
            }
        }
    }

    void APickUp::Update(double, ECS::Entity& entity)
    {
        if (entity.HasComponent<Transform>()) {
            Transform& transform = entity.GetComponent<Transform>();
            if (Engine::GameConfiguration::GetDebugMode()) {
                RayLib::Window::GetInstance(0, "")->DrawSphereWires(transform.position, _pickupRadius);
            }
            transform.rotation.y += 1.0f;
        }
    }

    int APickUp::getPlayerNbr(const std::string &tag)
    {
        for (unsigned int i = 0; tag[i]; i++) {
            if (tag[i] >= '0' && tag[i] <= '9')
                return std::stoi(&tag[i]);
        }
        return -1;
    }
}
