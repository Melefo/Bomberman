/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#include "PhysicsBody.hpp"

namespace RayLib
{
	PhysicsBody::PhysicsBody(const RayLib::Vector2<float>& pos, float radius, float density) :
	_physicsBody(std::make_unique<::PhysicsBodyData>(::CreatePhysicsBodyCircle(pos.getVector2(), radius, density)))
	{
		this->_physicsBody->enabled = false;
	}

	PhysicsBody::PhysicsBody(const RayLib::Vector2<float>& pos, float width, float height, float density) :
	_physicsBody(std::make_unique<::PhysicsBodyData>(::CreatePhysicsBodyRectangle(pos.getVector2(), width, height, density)))
	{
		this->_physicsBody->enabled = false;
	}

	PhysicsBody::PhysicsBody(const RayLib::Vector2<float>& pos, float radius, int sides, float density) :
	_physicsBody(std::make_unique<::PhysicsBodyData>(::CreatePhysicsBodyPolygon(pos.getVector2(), radius, sides, density)))
	{
		this->_physicsBody->enabled = false;
	}

	PhysicsBody::~PhysicsBody()
	{
		::DestroyPhysicsBody(this->_physicsBody.get());
	}

	void PhysicsBody::InitPhysics(void)
	{
		::InitPhysics();
	}

	void PhysicsBody::InitPhysics(void)
	{
		::ClosePhysics();
	}

	bool PhysicsBody::IsPhysicsEnabled(void)
	{
		return ::IsPhysicsEnabled();
	}

	::PhysicsBodyData& PhysicsBody::GetPhysicsBody()
	{
		return *this->_physicsBody;
	}
}
