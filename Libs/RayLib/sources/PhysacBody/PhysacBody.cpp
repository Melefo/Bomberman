/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#include "PhysacBody.hpp"

namespace RayLib
{
	PhysacBody::PhysacBody(const RayLib::Vector2<float>& pos, float radius, float density) :
	_physicsBody(::CreatePhysicsBodyCircle(pos.getVector2(), radius, density))
	//_physicsBody(std::make_unique<::PhysicsBodyData>(::CreatePhysicsBodyCircle(pos.getVector2(), radius, density)))
	{
		this->_physicsBody->enabled = false;
	}

	PhysacBody::PhysacBody(const RayLib::Vector2<float>& pos, float width, float height, float density) :
	_physicsBody(::CreatePhysicsBodyRectangle(pos.getVector2(), width, height, density))
	{
		this->_physicsBody->enabled = false;
	}

	PhysacBody::PhysacBody(const RayLib::Vector2<float>& pos, float radius, int sides, float density) :
	_physicsBody(::CreatePhysicsBodyPolygon(pos.getVector2(), radius, sides, density))
	{
		this->_physicsBody->enabled = false;
	}

	PhysacBody::~PhysacBody()
	{
		::DestroyPhysicsBody(this->_physicsBody);

		//::DestroyPhysicsBody(this->_physicsBody.get());
	}

	void PhysacBody::InitPhysics(void)
	{
		::InitPhysics();
	}

	void PhysacBody::ClosePhysics(void)
	{
		::ClosePhysics();
	}

	bool PhysacBody::IsPhysicsEnabled(void)
	{
		return ::IsPhysicsEnabled();
	}

	::PhysicsBodyData& PhysacBody::GetPhysicsBody()
	{
		return *this->_physicsBody;
	}

	void PhysacBody::SetPosition(const RayLib::Vector2<float>& pos)
	{
		this->_physicsBody->position = pos.getVector2();
	}

	RayLib::Vector2<float> PhysacBody::GetPosition(void)
	{
		return (this->_physicsBody->position);
	}

	void PhysacBody::SetRectScale(const RayLib::Vector2<float>& scale)
	{
		this->_physicsBody->shape.vertexData = CreateRectanglePolygon(this->_physicsBody->position, scale.getVector2());
	}

	void PhysacBody::SetCircleRadiusScale(float radius)
	{
		this->_physicsBody->shape.radius = radius;
	}
}
