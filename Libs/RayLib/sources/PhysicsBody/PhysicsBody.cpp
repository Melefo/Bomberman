/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#include "PhysicsBody.hpp"

namespace RayLib
{
	PhysicsBody::PhysicsBody(RayLib::Vector2 pos, float radius, float density) :
	{
	}

	PhysicsBody::PhysicsBody(RayLib::Vector2 pos, float width, float height, float density)
	{

	}

	PhysicsBody::PhysicsBody(RayLib::Vector2 pos, float radius, int sides, float density)
	{

	}

	void PhysicsBody::InitPhysics(void)
	{
		::InitPhysics();
	}

	bool PhysicsBody::IsPhysicsEnabled(void)
	{
		return ::IsPhysicsEnabled();
	}
}
