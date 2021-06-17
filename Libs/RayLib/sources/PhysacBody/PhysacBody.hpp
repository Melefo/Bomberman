/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#ifndef PHYSACBODY_HPP_
#define PHYSACBODY_HPP_

#include <memory>
#include "Vector2.hpp"
#define PHYSAC_IMPLEMENTATION

#include <physac.h>

namespace RayLib
{
	class PhysacBody
	{
		public:
			PhysacBody(const RayLib::Vector2<float>& pos, float radius, float density);
			PhysacBody(const RayLib::Vector2<float>& pos, float width, float height, float density);
			PhysacBody(const RayLib::Vector2<float>& pos, float radius, int sides, float density);
			~PhysacBody();

			static void InitPhysics(void);
			static void ClosePhysics(void);
			static bool IsPhysicsEnabled(void);

			::PhysicsBodyData& GetPhysicsBody();
			RayLib::Vector2<float> GetPosition(void);
			void SetPosition(const RayLib::Vector2<float>& pos);

			void SetRectScale(const RayLib::Vector2<float>& scale);
			void SetCircleRadiusScale(float radius);

		private:
			::PhysicsBodyData *_physicsBody;

			//std::unique_ptr<::PhysicsBodyData> _physicsBody;
			//std::unique_ptr<PhysicsBody> _physicsBody;


	};
}

#endif // !PHYSICSBODY_HPP_
