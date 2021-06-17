/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics2D
*/

#include "Physics2D.hpp"

namespace Engine
{
    bool Physics2D::CheckCollision(RayLib::PhysacBody& body1, RayLib::PhysacBody& body2)
    {
        bool colliding = false;

        // create manifold
        // ! ceci est un raw ptr !
        ::PhysicsManifold manifold = ::CreatePhysicsManifold(&body1.GetPhysicsBody(), &body2.GetPhysicsBody());
        // solve collisions
        ::SolvePhysicsManifold(manifold);
        colliding = manifold->contactsCount > 0;

        PHYSAC_FREE(manifold);
        return (colliding);
    }

    bool Physics2D::IsColliding(ECS::Entity& body, std::vector<std::string> colmask)
    {
        if (body.OfType<Component::Collider>().size() == 0)
            throw (Engine::Exception::EngineException("Object has no collider!"));

        RayLib::PhysacBody& physacBody = body.OfType<Component::Collider>()[0].get().GetPhysacBody();
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

        // get all entities
        const std::list<std::unique_ptr<ECS::Entity>>& entities = coordinator->GetEntities();
        for (auto entity = entities.begin(); entity != entities.end(); entity++) {
            if (entity->get()->OfType<Component::Collider>().size() == 0)
                continue;
            if (entity->get()->GetId() == body.GetId())
                continue;
            RayLib::PhysacBody& physacBody2 = entity->get()->OfType<Component::Collider>()[0].get().GetPhysacBody();

            if (CheckCollision(physacBody, physacBody2))
                return (true);
        }
        return (false);
    }

    bool Physics2D::IsCollidingAtPosition(ECS::Entity& body, RayLib::Vector2<float> center, std::vector<std::string> colmask)
    {
        if (body.OfType<Component::Collider>().size() == 0)
            throw (Engine::Exception::EngineException("Object has no collider!"));

        bool collided = false;
        RayLib::PhysacBody& physacBody = body.OfType<Component::Collider>()[0].get().GetPhysacBody();
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

        RayLib::Vector2<float> originPos = physacBody.GetPosition();
        physacBody.SetPosition(center);
        // get all entities
        const std::list<std::unique_ptr<ECS::Entity>>& entities = coordinator->GetEntities();
        for (auto entity = entities.begin(); entity != entities.end(); entity++) {
            if (entity->get()->OfType<Component::Collider>().size() == 0)
                continue;
            if (entity->get()->GetId() == body.GetId())
                continue;
            RayLib::PhysacBody& physacBody2 = entity->get()->OfType<Component::Collider>()[0].get().GetPhysacBody();

            if (CheckCollision(physacBody, physacBody2)) {
                collided = true;
                break;
            }
        }
        physacBody.SetPosition(originPos);
        return (collided);
    }

    void Physics2D::DrawLines(ECS::Entity& body)
    {
        // window draw square ?
    }

    ECS::Entity& Physics2D::GetCollision(ECS::Entity& body, std::vector<std::string> colMask)
    {
        if (body.OfType<Component::Collider>().size() == 0)
            throw (Engine::Exception::EngineException("Object has no collider!"));

        RayLib::PhysacBody& physacBody = body.OfType<Component::Collider>()[0].get().GetPhysacBody();
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

        // get all entities
        const std::list<std::unique_ptr<ECS::Entity>>& entities = coordinator->GetEntities();
        for (auto entity = entities.begin(); entity != entities.end(); entity++) {
            if (entity->get()->OfType<Component::Collider>().size() == 0)
                continue;
            if (entity->get()->GetId() == body.GetId())
                continue;
            RayLib::PhysacBody& physacBody2 = entity->get()->OfType<Component::Collider>()[0].get().GetPhysacBody();

            if (CheckCollision(physacBody, physacBody2))
                return (*entity->get());
        }

        throw (Engine::Exception::EngineException("Not colliding with anything"));
    }

    ECS::Entity& Physics2D::GetCollisionPosition(ECS::Entity& body, RayLib::Vector2<float> center, std::vector<std::string> colmask)
    {
        if (body.OfType<Component::Collider>().size() == 0)
            throw (Engine::Exception::EngineException("Object has no collider!"));

        bool collided = false;
        RayLib::PhysacBody& physacBody = body.OfType<Component::Collider>()[0].get().GetPhysacBody();
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

        RayLib::Vector2<float> originPos = physacBody.GetPosition();
        physacBody.SetPosition(center);
        // get all entities
        const std::list<std::unique_ptr<ECS::Entity>>& entities = coordinator->GetEntities();
        for (auto entity = entities.begin(); entity != entities.end(); entity++) {
            if (entity->get()->OfType<Component::Collider>().size() == 0)
                continue;
            if (entity->get()->GetId() == body.GetId())
                continue;
            RayLib::PhysacBody& physacBody2 = entity->get()->OfType<Component::Collider>()[0].get().GetPhysacBody();

            if (CheckCollision(physacBody, physacBody2)) {
                physacBody.SetPosition(originPos);
                return (*entity->get());
            }
        }
        throw (Engine::Exception::EngineException("Not colliding with anything"));
    }

    void InitPhysics(void)
    {
        ::InitPhysics();
    }

    void ClosePhysics(void)
    {
        ::ClosePhysics();
    }


}

