/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Particle
*/

#include "Particle.hpp"
#include "PhysicsBody.hpp"
#include "Drawable3D.hpp"
#include "Window.hpp"
#include "Transform.hpp"
#include "Physics2D.hpp"

namespace Component
{
    Particle::Particle(float startSpeed, float lifeTime) : _lifeTimer(lifeTime), _speed(startSpeed), _direction()
    {
        static int i = 0;

        std::srand(static_cast<unsigned int>(time(NULL)) + i);

        while (_direction == RayLib::Vector3()) {
            _direction.x = static_cast<float>(-1 + std::rand() % 3);
            _direction.y = static_cast<float>(std::rand() % 2);
            _direction.z = static_cast<float>(-1 + std::rand() % 3);

            /*_direction.x = RayLib::Physics2D::RandomFloat(-1.0f, 1.0f);
            _direction.y = RayLib::Physics2D::RandomFloat(0.0f, 1.0f);
            _direction.z = RayLib::Physics2D::RandomFloat(-1.0f, 1.0f);*/
        }

        _speed += RayLib::Physics2D::RandomFloat(-0.25f, 0.25f);

        i++;
    }

    void Particle::Update(double, ECS::Entity& entity)
    {
        if (entity.HasComponent<Component::Transform>()) {
            Transform& transform = entity.GetComponent<Component::Transform>();
            transform.rotation += _direction;
        }

        if (entity.HasComponent<Component::PhysicsBody>()) {
            // set vel = directino * speed
            entity.GetComponent<Component::PhysicsBody>().velocity = _direction * _speed;
        }

        if (entity.HasComponent<Component::Drawable3D>()) {
            Component::Drawable3D& drawable = entity.GetComponent<Component::Drawable3D>();
            RayLib::Color current = drawable.GetColor();
            RayLib::Color newCol = current;
            RayLib::Color target = current;

            target.a = 0;

            if (current.a == 0) {
                entity.Dispose();
                return;
            }

            newCol.Lerp(target, 0.1f);
            drawable.SetColor(newCol);
        }

        _lifeTimer -= RayLib::Window::GetInstance(0, "")->GetFrameTime();
        if (_lifeTimer <= 0.0f) {
            entity.Dispose();
        }
    }

    void Particle::LateUpdate(double, ECS::Entity&)
    {

    }

    void Particle::FixedUpdate(ECS::Entity&)
    {

    }
}
