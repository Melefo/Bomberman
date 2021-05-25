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


            // privé ou public ?
            bool hit;               // Did the ray hit something?
            float distance;         // Distance to nearest hit
            Vector3 position;       // Position of nearest hit
            Vector3 normal;         // Surface normal of hit

        protected:
        private:
    };
}

#endif /* !RAYHITINFO_HPP_ */
