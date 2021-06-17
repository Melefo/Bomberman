/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#ifndef PHYSICSBODY_HPP_
#define PHYSICSBODY_HPP_

#include <memory>
#include "Vector2.hpp"
#define PHYSAC_IMPLEMENTATION

#include "physac.h"

namespace RayLib
{
	class PhysicsBody
	{
		public:
			PhysicsBody(const RayLib::Vector2<float>& pos, float radius, float density);
			PhysicsBody(const RayLib::Vector2<float>& pos, float width, float height, float density);
			PhysicsBody(const RayLib::Vector2<float>& pos, float radius, int sides, float density);
			~PhysicsBody();

			static void InitPhysics(void);
			static void ClosePhyics(void);
			static bool IsPhysicsEnabled(void);

			::PhysicsBodyData& GetPhysicsBody();

		// ! floor->enabled = false;         // Disable body state to convert it to static (no dynamics, but collisions)
		private:
			std::unique_ptr<::PhysicsBodyData> _physicsBody;
		
	};
}

#endif // !PHYSICSBODY_HPP_
