/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PlayerInputs
*/

#include "PlayerInputs.hpp"

namespace Component
{
    PlayerInputs::PlayerInputs(ECS::Entity& entity, RayLib::Input input, int dropBombKey, float speed, float dropDelay)
    : AController(entity, speed, dropDelay), _input(input), _window(RayLib::Window::GetInstance(0, "")), _bombKey(dropBombKey), _entity(entity)
    {
    }


    void PlayerInputs::Update(double dt, ECS::Entity& entity)
    {
        float windowFrameTime = _window->GetFrameTime();

        if (_dropBomb.timeToDrop > 0.0f) {
            _dropBomb.timeToDrop -= windowFrameTime;
        }

        if (_input.IsKeyDown(_bombKey) && _dropBomb.timeToDrop <= 0.0f) {

            // ! keep this transform in cache ?
            if (_entity.HasComponent<Transform>()) {
                Transform& transform = _entity.GetComponent<Transform>();
                _dropBomb.InstantiateBomb(transform.position, Explosion::ExplosionType::CIRCLE);
                std::cout << "Instantiate bomb" << std::endl;

                _dropBomb.timeToDrop = _dropBomb.GetDropDelay();
            }
        }

        //std::vector<std::reference_wrapper<Collider>> colliders = _entity.OfType<Collider>();

        //for (auto it = colliders.begin(); it != colliders.end(); it++) {
        //    it->get().DrawLines();
        //}
        _movement.direction = RayLib::Vector3(_input.GetHorizontalAxis(), 0.0f, _input.GetVerticalAxis());

        _movement.Update(dt, entity);
        _dropBomb.Update();
    }

    void PlayerInputs::FixedUpdate(ECS::Entity& entity)
    {
        _movement.FixedUpdate(entity);
    }

    void PlayerInputs::LateUpdate(double, ECS::Entity&)
    {

    }

}

