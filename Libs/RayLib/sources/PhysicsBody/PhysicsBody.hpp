/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#ifndef PHYSICSBODY_HPP_
#define PHYSICSBODY_HPP_

#include "physac.h"

namespace RayLib
{
	class PhysicsBody
	{
		public:
			PhysicsBody(RayLib::Vector2 pos, float radius, float density);
			PhysicsBody(RayLib::Vector2 pos, float width, float height, float density);
			PhysicsBody(RayLib::Vector2 pos, float radius, int sides, float density);

			static void InitPhysics(void);
			static bool IsPhysicsEnabled(void);

		// ! floor->enabled = false;         // Disable body state to convert it to static (no dynamics, but collisions)
		private:
			std::unique_ptr<PhysicsBodyData> _physicsBody;
		
	};
}

#endif // !PHYSICSBODY_HPP_
