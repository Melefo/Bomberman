/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Mouse
*/

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include <raylib.h>
#include "Vector2.hpp"

namespace RayLib
{
    class Mouse {
        public:
            Mouse();
            ~Mouse();

            static Vector2<float> getPosition();
            static bool isButtonDown(int button);
            static bool isButtonUp(int button);

        protected:
        private:
    };
}

#endif /* !MOUSE_HPP_ */
