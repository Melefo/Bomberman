/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RayHitInfo
*/

#ifndef RAYHITINFO_HPP_
#define RAYHITINFO_HPP_

#include "Vector3.hpp"

namespace RayLib
{
    class RayHitInfo {
        public:
            RayHitInfo();
            ~RayHitInfo();

            RayHitInfo(const RayHitInfo& other);
            RayHitInfo(const ::RayHitInfo& other);

            RayHitInfo& operator=(const RayHitInfo& other);
            RayHitInfo& operator=(const ::RayHitInfo& other);

            ::RayHitInfo GetHitInfo(void);

            bool HasHit(void);
            float GetDistance(void);
            Vector3& GetPosition(void);
            Vector3& GetNormal(void);

        protected:
        private:
            // privé ou public ?
            bool _hit;               // Did the ray hit something?
            float _distance;         // Distance to nearest hit
            Vector3 _position;       // Position of nearest hit
            Vector3 _normal;         // Surface normal of hit
    };
}

#endif /* !RAYHITINFO_HPP_ */
