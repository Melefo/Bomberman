/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** IDrawable
*/

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

#include <raylib.h>
#include "Vector3.hpp"
#include "Color.hpp"

namespace RayLib
{
    class IDrawable {
        public:
            IDrawable() = default;
            ~IDrawable() = default;

            virtual void Draw(RayLib::Vector3 position, RayLib::Vector3 scale, RayLib::Color tint) = 0;

        protected:
        private:
    };
}
#endif /* !IDRAWABLE_HPP_ */
